#pragma once
#include <string>

#include <opentracing/span.h>

#include "model/person.hpp"
#include "util/error.hpp"

namespace e5 {
/**
 * Sends a request for a person identified by `name` to the bigbrother_service
 * which manages the database.
 * @param ctx The tracing SpanContext to be injected into the message to send.
 * @param name The name that identifies the person we're looking for.
 * @return The resulting person object or an error on failure.
 */
tl::expected<model::person, util::error>
get_person(const opentracing::SpanContext* ctx, std::string&& name);
} // namespace e5
