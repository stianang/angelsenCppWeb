#include "ServerImplementation.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <json.hpp>
#include <thread>

#include <ControllerIndex.h>
#include <ControllerBlogPost.h>
#include <ControllerContact.h>

using namespace Angelsen;

template<typename SocketType>
void ServerImplementation<SocketType>::run(const Config& config, SimpleWeb::Server<SocketType>& server)
{
    defineDefaults(config, server);

    using ResponsePtr = std::shared_ptr<typename SimpleWeb::Server<SocketType>::Response>;
    using RequestPtr = std::shared_ptr<typename SimpleWeb::Server<SocketType>::Request>;

    ControllerIndex controllerIndex(config);
    ControllerBlogPost controllerBlogPost(config);
    ControllerContact controllerContact(config);

    server.resource["^/$"]["GET"] = [&controllerIndex](ResponsePtr response, RequestPtr) {
        response->write(controllerIndex.get());
    };

    server.resource["^/blog/(.*)/(.*html)$"]["GET"] = [&controllerBlogPost](ResponsePtr response, RequestPtr request) {
        response->write(controllerBlogPost.get(request->path));
    };

    server.resource["^/contact$"]["GET"] = [&controllerContact](ResponsePtr response, RequestPtr request) {
        json form = EasyWeb::HttpUtility::requestQueryToJson(request->parse_query_string());

        response->write(controllerContact.get({form["cf-name"].get<std::string>(),
                                     form["cf-email"].get<std::string>(),
                                     form["cf-number"].get<std::string>(),
                                     form["cf-subject"].get<std::string>(),
                                     form["cf-message"].get<std::string>()}));
    };

    auto thread = std::thread([&server]()
    {
        std::cout << "Server started\n";
        server.start();
    });

    thread.join();
}

template<typename SocketType>
void ServerImplementation<SocketType>::defineDefaults(const Config& config, SimpleWeb::Server<SocketType>& server)
{
    using ResponsePtr = std::shared_ptr<typename SimpleWeb::Server<SocketType>::Response>;
    using RequestPtr = std::shared_ptr<typename SimpleWeb::Server<SocketType>::Request>;
    using namespace std;
    // Route used to load resources, such as css, html, images, etc.
    server.default_resource["GET"] = [&config](ResponsePtr response, RequestPtr request) {

        const std::string path = config.templateDir +  request->path;

        try {
            SimpleWeb::CaseInsensitiveMultimap header;

            // Uncomment the following line to enable Cache-Control
            // header.emplace("Cache-Control", "max-age=86400");

            auto ifs = make_shared<ifstream>();
            ifs->open(path, ifstream::in | ios::binary | ios::ate);

            if(*ifs) {
                auto length = ifs->tellg();
                ifs->seekg(0, ios::beg);

                header.emplace("Content-Length", to_string(length));
                response->write(header);

                // Trick to define a recursive function within this scope (for example purposes)
                class FileServer {
                public:
                    static void read_and_send(const ResponsePtr &response, const shared_ptr<ifstream> &ifs) {
                        // Read and send 128 KB at a time
                        static vector<char> buffer(131072); // Safe when server is running on one thread
                        streamsize read_length;
                        if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
                            response->write(&buffer[0], read_length);
                            if(read_length == static_cast<streamsize>(buffer.size())) {
                                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                                    if(!ec)
                                        read_and_send(response, ifs);
                                    else
                                        cerr << "Connection interrupted" << endl;
                                });
                            }
                        }
                    }
                };
                FileServer::read_and_send(response, ifs);
            }
            else
                throw invalid_argument("could not read file");
        }
        catch(const exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
        }
    };

    server.on_error = [](RequestPtr /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
        std::cout << "Error handling request\n";
    };
}
