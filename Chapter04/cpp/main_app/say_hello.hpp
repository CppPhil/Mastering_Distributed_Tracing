#pragma once
#include <string>

#include <opentracing/span.h>

#include "util/error.hpp"

namespace e5 {
tl::expected<std::string, util::error> say_hello(opentracing::Span& span,
                                                 std::string&& name);
} // namespace e5
