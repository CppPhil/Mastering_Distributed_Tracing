#pragma once
#include <string>

#include <drogon/HttpRequest.h>

namespace model {
class person {
public:
  static person from_json(const std::string& json);

  person();

  person(std::string name, std::string title, std::string description);

  const std::string& name() const noexcept;

  void name(std::string&& s);

  const std::string& title() const noexcept;

  void title(std::string&& s);

  const std::string& description() const noexcept;

  void description(std::string&& s);

private:
  std::string name_;
  std::string title_;
  std::string description_;
};
} // namespace model

namespace drogon {
template <>
inline ::model::person fromRequest(const HttpRequest& req) {
  auto json_shared_ptr = req.getJsonObject();
  auto& json = *json_shared_ptr;

  ::model::person p;
  p.name(json["name"].asString());
  p.title(json["title"].asString());
  p.description(json["description"].asString());

  return p;
}
} // namespace drogon
