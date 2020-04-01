#include <utility>

#include "model/person.hpp"

namespace model {
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
} // namespace model
