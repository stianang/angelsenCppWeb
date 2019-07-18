#include "ControllerBlogPost.h"
#include <Jinja2CppLight.h>

using namespace Angelsen;

ControllerBlogPost::ControllerBlogPost(const Config &config)
    : config_(config)
{

}

std::string ControllerBlogPost::get(const std::string& blogPath)
{
    EasyWeb::WebFile blog(config_.templateDir + "/" + blogPath, false);

    Jinja2CppLight::Template t(config_.template_->file());
    t.setValue("body", blog.file());

    return t.render();
}
