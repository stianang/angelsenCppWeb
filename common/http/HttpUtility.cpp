#include "HttpUtility.h"

nlohmann::json EasyWeb::HttpUtility::requestQueryToJson(const SimpleWeb::CaseInsensitiveMultimap &request)
{
    json query;

    for(const auto &[key, value] : request)
        query[key] = value;

    return query;
}
