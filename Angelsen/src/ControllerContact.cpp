#include "ControllerContact.h"
#include <Jinja2CppLight.h>
#include <EmailClientSendInBlue.h>
#include <sstream>

using namespace Angelsen;

ControllerContact::ControllerContact(const Config &config)
    : config_(config),
      confirmation_(config.templateDir + "/contact_confirmation.html", config.reload)
{

}

std::string ControllerContact::get(const FormData &formData)
{
    Jinja2CppLight::Template confirmation(confirmation_.file());

    if (sendEmail(formData))
    {
        confirmation.setValue("headerTitle", "Thank you for your request!");
        confirmation.setValue("title", "Your request has been sent");
        confirmation.setValue("result", "We will contact you as soon as possible. For urgent request, please contact us on (+47) 90 07 98 93 or on stian@angelsensoftware.com" );
    }
    else
    {
        confirmation.setValue("headerTitle", "Something went wrong");
        confirmation.setValue("title", "We were unable to process your request");
        confirmation.setValue("result", "Please verify all fields were entered correctly. For urgent request, please contact us on (+47) 90 07 98 93  or on stian@angelsensoftware.com");
    }

    Jinja2CppLight::Template mainTemplate(config_.template_->file());
    mainTemplate.setValue("body", confirmation.render());

    return mainTemplate.render();
}


bool ControllerContact::sendEmail(const FormData &formData)
{
    std::stringstream html;
    html << "<h3>New message from your website!</h3>\n"
         << "<p>" << formData.message << "</p>\n"
         << "<h3>Info</h3>\n"
         << "<p>Name:    " << formData.name << "</p>\n"
         << "<p>Email:   " << formData.email << "</p>\n"
         << "<p>Number:  " << formData.number << "</p>\n"
         << "<p>Subject: " << formData.subject << "</p>\n";

    std::stringstream plain;
    plain << "New message from your website!\n\n"
          << formData.message << "\n\n"
          << "Info\n"
          << "Name:    " << formData.name << "\n"
          << "Email:   " << formData.email << "\n"
          << "Number:  " << formData.number << "\n"
          << "Subject: " << formData.subject << "\n";

    auto email = EmailClientSendInBlue(config_.email.url,
                                       config_.email.apiKey)
                    .to(config_.email.toEmail, config_.email.toName)
                    .from(formData.email, formData.name)
                    .subject(formData.subject)
                    .content(html.str(), plain.str());

    return email.send();
}
