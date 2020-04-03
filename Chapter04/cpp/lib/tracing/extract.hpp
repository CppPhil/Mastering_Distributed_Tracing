#pragma once
#include <cstddef>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <opentracing/tracer.h>

#include "util/error.hpp"

namespace tracing {
tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpRequest& http_request);

tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpResponse& http_response);
} // namespace tracing
