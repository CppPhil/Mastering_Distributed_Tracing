#pragma once
#include <string>

#include <opentracing/span.h>

#include "model/person.hpp"
#include "util/error.hpp"

namespace e5 {
tl::expected<std::string, util::error>
format_greeting(opentracing::Span& span, const model::person& person);
} // namespace e5
