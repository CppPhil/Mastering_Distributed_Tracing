#pragma once
#include <iosfwd>

#include <tl/expected.hpp>

#include "util/source_location.hpp"

namespace util {
class error {
public:
  explicit error(std::string error_message);

  [[nodiscard]] const std::string& message() const;

  template <class Exception>
  [[noreturn]] void throw_as() const {
    throw Exception(message());
  }

  friend std::ostream& operator<<(std::ostream& os, const error& e);

private:
  std::string error_message_;
};
} // namespace util

#define UTIL_MAKE_ERROR(message)                                               \
  ::util::error(::std::string(message)                                         \
                + "\nerror occurred at:\n" UTIL_SOURCE_LOCATION)

#define UTIL_UNEXPECTED(message) ::tl::make_unexpected(UTIL_MAKE_ERROR(message))
