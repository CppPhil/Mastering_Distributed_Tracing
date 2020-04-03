#pragma once
#include <string>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <opentracing/tracer.h>

#include "util/error.hpp"

namespace tracing {
tl::expected<std::string, util::error>
inject(const opentracing::SpanContext& sc);

tl::expected<void, util::error> inject(drogon::HttpResponse& http_response,
                                       const opentracing::SpanContext& sc);

tl::expected<void, util::error> inject(drogon::HttpRequest& http_request,
                                       const opentracing::SpanContext& sc);
} // namespace tracing
