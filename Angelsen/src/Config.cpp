#include "Config.h"

using namespace Angelsen;

void Config::loadTemplate()
{
    if (!templateDir.empty())
    {
        template_ = std::make_unique<EasyWeb::WebFile>(templateDir + "/template.html", reload);
    }
}
void Config::updateFromJson(const std::string &configPath)
{
    EasyWeb::WebFile jsonFile(configPath);
    json config = json::parse(jsonFile.file());

    rootDir     = config["rootDir"].get<std::string>();
    templateDir = config["templateDir"].get<std::string>();

    port = config["port"].get<unsigned short>();

    https = config["https"].get<bool>();
    crt   = config["crt"].get<std::string>();
    key   = config["key"].get<std::string>();
    reload = config["reload"].get<bool>();

    email.url     = config["email"]["url"].get<std::string>();
    email.apiKey  = config["email"]["apiKey"].get<std::string>();
    email.toEmail = config["email"]["toEmail"].get<std::string>();
    email.toName  = config["email"]["toName"].get<std::string>();
}
