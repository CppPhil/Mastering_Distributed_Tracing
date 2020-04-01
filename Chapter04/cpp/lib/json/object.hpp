#pragma once
#include <sstream>
#include <string>

#include <Poco/JSON/Object.h>

namespace json {
template <class... Ts>
std::string object(Ts&&... xs) {
  Poco::JSON::Object obj;

  (obj.set(xs.first, xs.second), ...);

  std::ostringstream oss;
  obj.stringify(oss);

  return oss.str();
}
} // namespace json
