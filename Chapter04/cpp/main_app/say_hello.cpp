#include <utility>

#include "format_greeting.hpp"
#include "get_person.hpp"
#include "say_hello.hpp"

namespace e4 {
tl::expected<std::string, util::error> say_hello(opentracing::Span& span,
                                                 std::string&& name) {
  const auto exp_person = get_person(&span.context(), std::move(name));

  if (exp_person.has_value()) {
    const auto exp_greeting = format_greeting(span, *exp_person);

    if (exp_greeting.has_value()) {
      return *exp_greeting;
    } else {
      return tl::make_unexpected(exp_greeting.error());
    }
  } else {
    return tl::make_unexpected(exp_person.error());
  }
}
} // namespace e4