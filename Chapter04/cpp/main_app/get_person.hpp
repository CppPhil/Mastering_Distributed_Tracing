#pragma once
#include <string>

#include <opentracing/span.h>

#include "model/person.hpp"
#include "util/error.hpp"

namespace e4 {
tl::expected<model::person, util::error>
get_person(const opentracing::SpanContext* ctx, std::string&& name);
} // namespace e4
