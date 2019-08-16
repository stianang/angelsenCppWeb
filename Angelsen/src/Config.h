#ifndef CONFIG_H
#define CONFIG_H

#include <json.hpp>
#include <WebFile.h>

using nlohmann::json;

namespace Angelsen
{
    struct Config
    {
        std::string rootDir;
        std::string templateDir;

        unsigned short port {8080};

        bool https {false};
        std::string crt;
        std::string key;
        bool reload{false};

        struct SendInBlue
        {
            std::string url;
            std::string apiKey;
            std::string toEmail;
            std::string toName;
        } email;

        std::unique_ptr<EasyWeb::WebFile> template_;

        void updateFromJson(const std::string &configPath);
        void loadTemplate();
    };
}



#endif // CONFIG_H
