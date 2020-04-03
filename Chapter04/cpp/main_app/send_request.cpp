#include <drogon/HttpClient.h>

#include "send_request.hpp"
#include "tracing/inject.hpp"

namespace e5 {
std::pair<drogon::ReqResult, drogon::HttpResponsePtr>
send_request(const opentracing::SpanContext* ctx,
             const std::string& operation_name, const std::string& host,
             const std::string& path, drogon::HttpRequestPtr& http_request) {
  auto http_client = drogon::HttpClient::newHttpClient(host);
  http_request->setPath(path);

  auto span = opentracing::Tracer::Global()->StartSpan(
    operation_name, {opentracing::ChildOf(ctx)});
  span->SetTag("span.kind", "client");
  span->SetTag("http.url", host + path);
  span->SetTag("http.method", http_request->getMethodString());

  const char* const body_data = http_request->bodyData();
  const size_t body_length = http_request->bodyLength();
  const std::string buf(body_data, body_length);
  span->SetTag("request.body", buf);

  tracing::inject(*http_request, span->context());

  return http_client->sendRequest(http_request);
}
} // namespace e5
