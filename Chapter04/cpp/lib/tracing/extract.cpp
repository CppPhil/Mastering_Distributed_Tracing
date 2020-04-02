#include <sstream>
#include <string>

#include "tracing/extract.hpp"

namespace tracing {
opentracing::expected<std::unique_ptr<opentracing::SpanContext>>
extract(const void* data, size_t byte_count) {
  std::string buf(static_cast<const char*>(data), byte_count);
  std::istringstream iss(buf);

  return opentracing::Tracer::Global()->Extract(iss);
}
} // namespace tracing
