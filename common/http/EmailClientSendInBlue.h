#ifndef EMAILCLIENTSENDINBLUE_H
#define EMAILCLIENTSENDINBLUE_H

#include "json.hpp"

using nlohmann::json;

class EmailClientSendInBlue
{
public:
    EmailClientSendInBlue(const std::string& url,
                          const std::string& apiKey);
    EmailClientSendInBlue& to(const std::string& email, const std::string name);
    EmailClientSendInBlue& subject(const std::string& subject);
    EmailClientSendInBlue& content(const std::string& htmlContent, const std::string& textContent);
    EmailClientSendInBlue& replyTo(const std::string& email);
    EmailClientSendInBlue& from(const std::string& email, const std::string name);

    std::string jsonToString();

    bool send();

private:
    json body_;
    const std::string url_;
    const std::string apiKey_;
};

#endif // EMAILCLIENTSENDINBLUE_H
