#pragma once
#include <memory>
#include <string>

#include <opentracing/span.h>

#include "util/error.hpp"

namespace tracing {
std::unique_ptr<opentracing::Span>
create_span(const tl::expected<std::unique_ptr<opentracing::SpanContext>,
                               util::error>& ctx,
            const std::string& operation_name);
} // namespace tracing
