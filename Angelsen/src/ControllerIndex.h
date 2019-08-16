#ifndef CONTROLLER_INDEX_H
#define CONTROLLER_INDEX_H

#include <WebFile.h>
#include <Config.h>
#include <ControllerBlogFeature.h>

namespace Angelsen
{
    struct ControllerIndex
    {
        ControllerIndex(const Config& config);

        std::string get();

        const Config& config_;
        ControllerBlogFeature controllerBlogFeature_;
        EasyWeb::WebFile index_;
    };
}


#endif // CONTROLLER_INDEX_H
