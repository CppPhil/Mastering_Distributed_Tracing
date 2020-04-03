#pragma once
#include <sstream>
#include <string>

#include <Poco/JSON/Object.h>

namespace json {
/**
 * Creates a string containing a JSON object from the pairs given.
 * @tparam Ts Must be a std::pair<std::string, X> where X is a type
 *         compatible with Poco::JSON::Object::set.
 * @param xs The pairs to create the JSON object from.
 * @return A string containing a JSON object where the .first
 *         data members of the pairs given are used as the JSON keys
 *         and the corresponding .second data members are used as
 *         their respective values.
 */
template <class... Ts>
std::string object(Ts&&... xs) {
  Poco::JSON::Object obj;

  (obj.set(xs.first, xs.second), ...);

  std::ostringstream oss;
  obj.stringify(oss);

  return oss.str();
}
} // namespace json
