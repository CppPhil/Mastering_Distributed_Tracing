#pragma once
#include <string>

#include <opentracing/span.h>

#include "model/person.hpp"
#include "util/error.hpp"

namespace e5 {
/**
 * Requests formatting of `person` from the formatter_service.
 * @param span The tracing Span to use. A greeting BaggageItem will be set for
 *             the Span.
 * @param person The person that the formatter_service shall format.
 * @return The resulting formatted greeting message string or an error on
 *         failure.
 */
tl::expected<std::string, util::error>
format_greeting(opentracing::Span& span, const model::person& person);
} // namespace e5
