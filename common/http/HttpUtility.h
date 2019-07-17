#ifndef HTTP_UTILITY_H
#define HTTP_UTILITY_H

#include <utility.hpp>
#include <json.hpp>

using nlohmann::json;

namespace EasyWeb::HttpUtility
{
    json requestQueryToJson(const SimpleWeb::CaseInsensitiveMultimap& request);
}

#endif // HTTP_UTILITY_H
