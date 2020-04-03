#pragma once
#include <string>
#include <utility>

#include <opentracing/span.h>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

namespace e4 {
std::pair<drogon::ReqResult, drogon::HttpResponsePtr>
send_request(const opentracing::SpanContext* ctx,
             const std::string& operation_name, const std::string& host,
             const std::string& path, drogon::HttpRequestPtr& http_request);
} // namespace e4
