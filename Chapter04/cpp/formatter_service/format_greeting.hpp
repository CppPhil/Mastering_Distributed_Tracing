#pragma once
#include <string>

#include <jaegertracing/Tracer.h>

#include <pl/string_view.hpp>

namespace e4 {
std::string format_greeting(
  pl::string_view name,
  pl::string_view title,
  pl::string_view description,
  const opentracing::SpanContext *ctx
);
} // namespace e4

