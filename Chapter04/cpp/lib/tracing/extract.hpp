#pragma once
#include <cstddef>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <opentracing/tracer.h>

#include "util/error.hpp"

namespace tracing {
/**
 * Extracts a serialized SpanContext from the HTTP headers.
 * @param http_request The HTTP request.
 * @return The SpanContext or an error on failure.
 */
tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpRequest& http_request);

/**
 * Extracts a serialized SpanContext from the HTTP headers.
 * @param http_response The HTTP response.
 * @return The SpanContext or an error on failure.
 */
tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpResponse& http_response);
} // namespace tracing
