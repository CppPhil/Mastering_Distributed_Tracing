#pragma once
#include <iosfwd>

#include <tl/expected.hpp>

#include "util/source_location.hpp"

namespace util {
/**
 * Type used to represent failure.
 */
class error {
public:
  /**
   * Creates an error object with a given `error_message`.
   * @param error_message The error message to use.
   */
  explicit error(std::string error_message);

  /**
   * Read accessor for the error message.
   * @return The error message.
   */
  [[nodiscard]] const std::string& message() const;

  /**
   * Throws an `Exception` using this object's error message.
   * @tparam Exception The type of the exception to throw.
   * @throws `Exception`.
   */
  template <class Exception>
  [[noreturn]] void throw_as() const {
    throw Exception(message());
  }

  /**
   * Output operator for error.
   * @param os The ostream to print to.
   * @param e The error object to print.
   * @return `os`.
   */
  friend std::ostream& operator<<(std::ostream& os, const error& e);

private:
  std::string error_message_;
};
} // namespace util

/**
 * @def UTIL_MAKE_ERROR(message)
 * Implementation macro to create an error object.
 */
#define UTIL_MAKE_ERROR(message)                                               \
  ::util::error(::std::string(message)                                         \
                + "\nerror occurred at:\n" UTIL_SOURCE_LOCATION)

/**
 * @def UTIL_UNEXPECTED(message)
 * Macro to create a tl::expected with an error
 */
#define UTIL_UNEXPECTED(message) ::tl::make_unexpected(UTIL_MAKE_ERROR(message))
