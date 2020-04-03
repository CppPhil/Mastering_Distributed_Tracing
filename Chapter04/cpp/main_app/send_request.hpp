#pragma once
#include <string>
#include <utility>

#include <opentracing/span.h>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

namespace e5 {
/**
 * Sends an HTTP request.
 * @param ctx The tracing SpanContext to be injected into the HTTP request to
 *            send.
 * @param operation_name The name of the operation to be performed for the
 *                       Tracer.
 * @param host The host part of the URL to send the request to, e.g.
 *             "http://localhost:8082"
 * @param path The path part of the URL to send the request to, e.g.
 *             "/formatGreeting"
 * @param http_request The HTTP request to send.
 * @return A pair containing a ReqResult and the HTTP response. The HTTP
 *         response may only be accessed if the ReqResult is Ok.
 * @warning The `http_request` must already have its HTTP method, content type
 *          and body set appropriately.
 */
std::pair<drogon::ReqResult, drogon::HttpResponsePtr>
send_request(const opentracing::SpanContext* ctx,
             const std::string& operation_name, const std::string& host,
             const std::string& path, drogon::HttpRequestPtr& http_request);
} // namespace e5
