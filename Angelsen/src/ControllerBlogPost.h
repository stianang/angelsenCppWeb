#ifndef CONTROLLER_BLOG_POST_H
#define CONTROLLER_BLOG_POST_H

#include <WebFile.h>
#include <Config.h>

namespace Angelsen
{
    struct ControllerBlogPost
    {
        ControllerBlogPost(const Config& config);

        std::string get(const std::string &blogPath);

        const Config& config_;
    };
}

#endif // CONTROLLER_BLOG_POST_H
