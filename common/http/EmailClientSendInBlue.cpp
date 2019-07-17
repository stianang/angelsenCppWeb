#include "EmailClientSendInBlue.h"
#include <client_https.hpp>
#include <iostream>


EmailClientSendInBlue::EmailClientSendInBlue(const std::string &url, const std::string &apiKey)
    : url_{url},
      apiKey_{apiKey}
{

}

EmailClientSendInBlue& EmailClientSendInBlue::to(const std::string& email, const std::string name)
{
    json to;
    to["email"] = email;
    to["name"] = name;

    body_["to"].push_back(to);

    return *this;
}

EmailClientSendInBlue& EmailClientSendInBlue::subject(const std::string& subject)
{
    body_["subject"] = subject;
    return *this;
}

EmailClientSendInBlue& EmailClientSendInBlue::content(const std::string& htmlContent, const std::string& textContent)
{
    body_["htmlContent"] = htmlContent;
    body_["textContent"] = textContent;
    return *this;
}

EmailClientSendInBlue& EmailClientSendInBlue::replyTo(const std::string& email)
{
    body_["replyTo"]["email"] = email;
    return *this;
}

EmailClientSendInBlue& EmailClientSendInBlue::from(const std::string& email, const std::string name)
{
    body_["sender"]["name"] = name;
    body_["sender"]["email"] = email;
    return *this;
}

std::string EmailClientSendInBlue::jsonToString()
{
    return body_.dump();
}

bool EmailClientSendInBlue::send()
{
    SimpleWeb::Client<SimpleWeb::HTTPS> client(url_, true);

    // Synchronous request examples
    std::string body = body_.dump();

    std::cout << "Send email request: " << body << std::endl;

    try {
        SimpleWeb::CaseInsensitiveMultimap header;
        header.emplace("Content-Type", "application/json");
        header.emplace("api-key", apiKey_ );

        auto r2 = client.request("POST", "/v3/smtp/email", body, header);
        std::cout << "Response:" << r2->content.string() << std::endl;
    }
    catch(const SimpleWeb::system_error &e) {
        std::cerr << "Client request error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

