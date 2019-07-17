#ifndef SERVERIMPLEMENTATION_H
#define SERVERIMPLEMENTATION_H

#include <Config.h>
#include <HttpUtility.h>
#include <server_http.hpp>
#include <server_https.hpp>
#include <iostream>

namespace Angelsen
{
    template<typename SocketType>
    struct ServerImplementation
    {
        void run(const Config& config, SimpleWeb::Server<SocketType>& server);
        void defineDefaults(const Config& config, SimpleWeb::Server<SocketType>& server);
    };

    void runServer(const Config& config);
}


void Angelsen::runServer(const Config& config)
{
    using SimpleWeb::Server;
    using SimpleWeb::HTTP;
    using SimpleWeb::HTTPS;

    if (config.https)
    {
        Server<HTTPS> server(config.crt, config.key);
        server.config.port = config.port;

        std::cout << "Serving as HTTPS server on port: " << config.port << "\n";

        Angelsen::ServerImplementation<HTTPS> angelsen;
        angelsen.run(config, server);
    }
    else
    {
        Server<HTTP> server;
        server.config.port = config.port;

        std::cout << "Serving as HTTP server on port: " << config.port << "\n";

        Angelsen::ServerImplementation<HTTP> angelsen;
        angelsen.run(config, server);
    }
}

#include <ServerImplementation.tpp>


#endif // SERVERIMPLEMENTATION_H
