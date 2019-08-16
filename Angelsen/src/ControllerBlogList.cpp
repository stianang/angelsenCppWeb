#include "ControllerBlogList.h"
#include <Jinja2CppLight.h>

using namespace Angelsen;
using std::string;

ControllerBlogList::ControllerBlogList(const Config &config)
    : config_(config),
      controllerBlogFeature_(config),
      blogListTemplate_{config.templateDir + "/blog_list.html", config.reload}
{
    EasyWeb::WebFile blogListJson(config.templateDir + "/blog/blogList.json");
    blogListJson_ = json::parse(blogListJson.file());
}

std::string ControllerBlogList::getList(int limit)
{
    bool useLimit = limit > 0;

    std::stringstream blogList;
    blogList << "<table><th>Date</th><th>Title</th>";

    int posts = 1;

    for (const auto& post : blogListJson_)
    {
        Jinja2CppLight::Template tListItem(R"(<tr><td>{{date}}</td><td><a href="{{a_href}}" target="_blank"ul>{{title}}</a></td></tr>)");
        tListItem.setValue("a_href", post["a_href"].get<string>());
        tListItem.setValue("title",  post["title"].get<string>());
        tListItem.setValue("date",   post["date"].get<string>());

        blogList << tListItem.render();

        if (useLimit && (++posts >= limit))
        {
            break;
        }
    }

    blogList << "</table>";

    return blogList.str();
}

std::string ControllerBlogList::get(int limit)
{
    Jinja2CppLight::Template tBlogList(blogListTemplate_.file());
    tBlogList.setValue("blog_feature", controllerBlogFeature_.get("Featured", false));
    tBlogList.setValue("blog_list", getList(limit));


    Jinja2CppLight::Template t(config_.template_->file());
    t.setValue("body", tBlogList.render());

    return t.render();
}
