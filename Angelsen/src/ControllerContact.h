#ifndef CONTROLLER_CONTACT_H
#define CONTROLLER_CONTACT_H

#include <WebFile.h>
#include <Config.h>

namespace Angelsen
{
    struct ControllerContact
    {
        ControllerContact(const Config& config);

        struct FormData
        {
            std::string name{};
            std::string email{};
            std::string number{};
            std::string subject{};
            std::string message{};
        };

        std::string get(const FormData &formData);
        bool sendEmail(const FormData& formData);

        const Config& config_;
        EasyWeb::WebFile confirmation_;
    };
}


#endif // CONTROLLER_CONTACT_H
