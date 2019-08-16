#ifndef CONTROLLERBLOGFEATURE_H
#define CONTROLLERBLOGFEATURE_H

#include <WebFile.h>
#include <Config.h>

namespace Angelsen
{
    struct ControllerBlogFeature
    {
        ControllerBlogFeature(const Config& config);

        std::string get(const std::string title = "Blog", bool blogLink = false);

        const Config& config_;
        nlohmann::json blogFeatureJson_;
        EasyWeb::WebFile blogFeature_;
        EasyWeb::WebFile blogFeatureElement_;
    };
}


#endif // CONTROLLERBLOGFEATURE_H
