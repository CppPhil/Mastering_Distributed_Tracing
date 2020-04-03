#pragma once
#include <memory>
#include <string>

#include <opentracing/span.h>

#include "util/error.hpp"

namespace tracing {
/**
 * Attempts to create a Span which is a child of the given SpanContext
 * that was deserialized from an incoming request.
 * @param ctx The result of a call to `tracing::extract`.
 * @param operation_name What name to use for the Span to be created.
 * @return The resulting Span.
 * @note The Span returned will be a child of the SpanContext in `ctx`
 *       if there's one, otherwise the new Span will not be associated
 *       with any other Span.
 */
std::unique_ptr<opentracing::Span>
create_span(const tl::expected<std::unique_ptr<opentracing::SpanContext>,
                               util::error>& ctx,
            const std::string& operation_name);
} // namespace tracing
