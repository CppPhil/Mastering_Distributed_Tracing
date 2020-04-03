#include <sstream>
#include <string>

#include <pl/unhexify.hpp>

#include "tracing/extract.hpp"

namespace tracing {
opentracing::expected<std::unique_ptr<opentracing::SpanContext>>
extract(const void* data, size_t byte_count) {
  std::string buf(static_cast<const char*>(data), byte_count);
  std::istringstream iss(buf);

  return opentracing::Tracer::Global()->Extract(iss);
}

namespace {
template <class T>
tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract_impl(const T& x) {
  const std::string& header_value_hex_string
    = x.getHeader("OPENTRACING_SPAN_CONTEXT");

  const std::vector<pl::byte> data(pl::unhexify(header_value_hex_string, 0));

  opentracing::expected<std::unique_ptr<opentracing::SpanContext>> exp(
    extract(data.data(), data.size()));

  if (!exp.has_value()) {
    std::ostringstream oss;
    oss << exp.error();
    return UTIL_UNEXPECTED(oss.str());
  }

  return *std::move(exp);
}
} // namespace

tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpRequest& http_request) {
  return extract_impl(http_request);
}

tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error>
extract(const drogon::HttpResponse& http_response) {
  return extract_impl(http_response);
}
} // namespace tracing
