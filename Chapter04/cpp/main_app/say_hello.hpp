#pragma once
#include <string>

#include <opentracing/span.h>

#include "util/error.hpp"

namespace e5 {
/**
 * Requests database contents for the person identified by `name` from the
 * bigbrother_service and then requests the formatter_service to create a
 * formatted greeting message.
 * @param span The tracing Span to use.
 * @param name The name that identifies the person.
 * @return The formatted greeting message to be sent back to our requester or an
 *         error on failure.
 */
tl::expected<std::string, util::error> say_hello(opentracing::Span& span,
                                                 std::string&& name);
} // namespace e5
