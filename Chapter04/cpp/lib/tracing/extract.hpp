#pragma once
#include <cstddef>

#include <opentracing/tracer.h>

namespace tracing {
opentracing::expected<std::unique_ptr<opentracing::SpanContext>>
extract(const void* data, size_t byte_count);
} // namespace tracing
