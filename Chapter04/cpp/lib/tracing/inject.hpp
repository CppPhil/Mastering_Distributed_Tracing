#pragma once
#include <string>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <opentracing/tracer.h>

#include "util/error.hpp"

namespace tracing {
/**
 * Injects a SpanContext into HTTP headers.
 * @param http_response The HTTP response.
 * @param sc The SpanContext to serialize.
 * @return Nothing on success. An error on failure.
 */
tl::expected<void, util::error> inject(drogon::HttpResponse& http_response,
                                       const opentracing::SpanContext& sc);

/**
 * Injects a SpanContext into HTTP headers.
 * @param http_request The HTTP request.
 * @param sc The SpanContext to serialize.
 * @return Nothing on success. An error on failure.
 */
tl::expected<void, util::error> inject(drogon::HttpRequest& http_request,
                                       const opentracing::SpanContext& sc);
} // namespace tracing
