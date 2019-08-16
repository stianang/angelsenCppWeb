#include "ControllerIndex.h"
#include <Jinja2CppLight.h>

Angelsen::ControllerIndex::ControllerIndex(const Config &config)
    : config_(config),
      controllerBlogFeature_(config),
      index_(config.templateDir + "/index.html", config.reload)
{

}

std::string Angelsen::ControllerIndex::get()
{
    Jinja2CppLight::Template tIndex(index_.file());
    tIndex.setValue("blog_feature", controllerBlogFeature_.get("Blog", true));

    Jinja2CppLight::Template t(config_.template_->file());
    t.setValue("body", tIndex.render());

    return t.render();
}
