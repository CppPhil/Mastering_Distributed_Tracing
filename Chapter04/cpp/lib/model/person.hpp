#pragma once
#include <string>

#include <drogon/HttpRequest.h>

namespace model {
class person {
public:
  person(std::string name, std::string title, std::string description);

  const std::string& name() const noexcept;

  const std::string& title() const noexcept;

  const std::string& description() const noexcept;

private:
  std::string name_;
  std::string title_;
  std::string description_;
};
} // namespace model

namespace drogon {
template <>
inline ::model::person fromRequest(const HttpRequest& req) {
  auto json = req.getJsonObject();
  ::model::person p(json["name"].asString(), json["title"].asString(),
                    json["description"].asString());
  return p;
}
} // namespace drogon
