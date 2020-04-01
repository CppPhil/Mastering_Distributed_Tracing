#include <utility>

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

#include "model/person.hpp"
#include "json/object.hpp"

namespace model {
person person::from_json(const std::string& json) {
  Poco::JSON::Parser parser;
  auto result = parser.parse(json);

  Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

  auto name = object->get("name");
  auto title = object->get("title");
  auto description = object->get("description");

  return person(name.toString(), title.toString(), description.toString());
}

person::person() : person("", "", "") {
  // nop
}

person::person(std::string name, std::string title, std::string description)
  : name_(std::move(name)),
    title_(std::move(title)),
    description_(std::move(description)) {
  // nop
}

const std::string& person::name() const noexcept {
  return name_;
}

void person::name(std::string&& s) {
  name_ = std::move(s);
}

const std::string& person::title() const noexcept {
  return title_;
}

void person::title(std::string&& s) {
  title_ = std::move(s);
}

const std::string& person::description() const noexcept {
  return description_;
}

void person::description(std::string&& s) {
  description_ = std::move(s);
}

std::string person::to_json() const {
  return json::object(std::pair{"name", name()}, std::pair{"title", title()},
                      std::pair{"description", description()});
}
} // namespace model
