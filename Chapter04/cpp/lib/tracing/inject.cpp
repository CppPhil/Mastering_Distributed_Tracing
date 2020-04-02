#include <sstream>

#include "tracing/inject.hpp"

namespace tracing {
tl::expected<std::vector<pl::byte>, util::error>
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

  const std::string buf(oss.str());
  return std::vector<pl::byte>(buf.begin(), buf.end());
}
} // namespace tracing
