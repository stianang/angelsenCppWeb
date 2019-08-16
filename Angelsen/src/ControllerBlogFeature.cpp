#include "ControllerBlogFeature.h"
#include <Jinja2CppLight.h>

using namespace Angelsen;
using std::string;

ControllerBlogFeature::ControllerBlogFeature(const Config &config)
    : config_(config),
      blogFeature_(config.templateDir + "/blog_feature.html", config.reload),
      blogFeatureElement_(config.templateDir + "/blog_feature_element.html", config.reload)
{
    EasyWeb::WebFile blogFeatureJson(config.templateDir + "/blog/blogList.json");
    blogFeatureJson_ = json::parse(blogFeatureJson.file());
}

std::string ControllerBlogFeature::get(const std::string title, bool blogLink)
{
    const string blogFeatureElement = blogFeatureElement_.file();

    std::stringstream blogElements;

    for (const auto& feature : blogFeatureJson_)
    {
        if (feature["feature"].get<bool>())
        {
            Jinja2CppLight::Template t(blogFeatureElement);
            t.setValue("date",       feature["date"].get<string>());
            t.setValue("title",      feature["title"].get<string>());
            t.setValue("description",feature["description"].get<string>());
            t.setValue("a_href",     feature["a_href"].get<string>());
            t.setValue("img_src",    feature["img_src"].get<string>());

            blogElements << t.render();
        }
    }

    Jinja2CppLight::Template tFeature(blogFeature_.file());
    tFeature.setValue("blog_feature_elements", blogElements.str());
    tFeature.setValue("title", title);

    if (blogLink)
    {
        tFeature.setValue("blog_link", R"(<p>&nbsp;</p><h3><a href="/bloglist">Go to blog</a></h3>)");
    }
    else
    {
        tFeature.setValue("blog_link", "");
    }

    return tFeature.render();
}

