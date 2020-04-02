#pragma once
#include <vector>

#include <opentracing/tracer.h>

#include <pl/byte.hpp>

#include "util/error.hpp"

namespace tracing {
tl::expected<std::vector<pl::byte>, util::error>
inject(const opentracing::SpanContext& sc);
} // namespace tracing
