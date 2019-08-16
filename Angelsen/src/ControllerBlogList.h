#ifndef CONTROLLERBLOGLIST_H
#define CONTROLLERBLOGLIST_H

#include <WebFile.h>
#include <Config.h>
#include <ControllerBlogFeature.h>

namespace Angelsen
{
    struct ControllerBlogList
    {
        ControllerBlogList(const Config& config);

        std::string getList(int limit);
        std::string get(int limit = 0);

        const Config& config_;
        nlohmann::json blogListJson_;
        ControllerBlogFeature controllerBlogFeature_;
        EasyWeb::WebFile blogListTemplate_;
    };
}


#endif // CONTROLLERBLOGLIST_H
