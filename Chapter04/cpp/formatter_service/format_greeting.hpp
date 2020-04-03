#pragma once
#include <string>

#include <jaegertracing/Tracer.h>

#include <pl/string_view.hpp>

namespace e5 {
/**
 * Formats a greeting message.
 * @param name The name of the person.
 * @param title The tile of the person.
 * @param description The description of the person.
 * @param ctx The SpanContext to create a tracing child Span from.
 * @return The resulting string.
 */
std::string format_greeting(pl::string_view name, pl::string_view title,
                            pl::string_view description,
                            const opentracing::SpanContext* ctx);
} // namespace e5
