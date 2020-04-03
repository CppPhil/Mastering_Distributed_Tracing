#include <sstream>

#include <pl/hexify.hpp>

#include "tracing/inject.hpp"

namespace tracing {
namespace {
tl::expected<std::string, util::error>
inject(const opentracing::SpanContext& sc) {
  std::ostringstream oss;

  const opentracing::expected<void> exp(
    opentracing::Tracer::Global()->Inject(sc, oss));

  if (!exp.has_value()) {
    oss.clear();
    oss.str("");

    oss << exp.error();

    return UTIL_UNEXPECTED(oss.str());
  }

  return oss.str();
}

template <class T>
tl::expected<void, util::error>
inject_impl(T& x, const opentracing::SpanContext& sc) {
  tl::expected<std::string, util::error> exp(inject(sc));

  if (!exp.has_value())
    return tl::make_unexpected(exp.error());

  const std::string& bytes = *exp;
  x.addHeader("OPENTRACING_SPAN_CONTEXT",
              pl::hexify(bytes.data(), bytes.size(), ""));
  return {};
}
} // namespace

tl::expected<void, util::error> inject(drogon::HttpResponse& http_response,
                                       const opentracing::SpanContext& sc) {
  return inject_impl(http_response, sc);
}

tl::expected<void, util::error> inject(drogon::HttpRequest& http_request,
                                       const opentracing::SpanContext& sc) {
  return inject_impl(http_request, sc);
}
} // namespace tracing
