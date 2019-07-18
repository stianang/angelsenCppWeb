#include "ControllerIndex.h"
#include <Jinja2CppLight.h>

Angelsen::ControllerIndex::ControllerIndex(const Config &config)
    : config_(config),
      index_(config.templateDir + "/index.html", true)
{

}

std::string Angelsen::ControllerIndex::get()
{
    Jinja2CppLight::Template t(config_.template_->file());
    t.setValue("body", index_.file());

    return t.render();
}
