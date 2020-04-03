#include <sstream>

#include "format_greeting.hpp"

namespace e4 {
std::string format_greeting(pl::string_view name, pl::string_view title,
                            pl::string_view description,
                            const opentracing::SpanContext* ctx) {
  auto span = opentracing::Tracer::Global()->StartSpan(
    "format-greeting", {opentracing::ChildOf(ctx)});

  std::string greeting(span->BaggageItem("greeting"));

  if (greeting.empty())
    greeting = "Hello";

  std::ostringstream oss;
  oss << greeting << ", ";

  if (!title.empty())
    oss << title << ' ';

  oss << name << '!';

  if (!description.empty())
    oss << ' ' << description;

  return oss.str();
}
} // namespace e4
