#pragma once
#include <cstddef>

#include <drogon/HttpRequest.h>

#include <opentracing/tracer.h>

#include "util/error.hpp"

namespace tracing {
opentracing::expected<std::unique_ptr<opentracing::SpanContext>>
extract(const void* data, size_t byte_count);

tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpRequest& http_request);
} // namespace tracing
