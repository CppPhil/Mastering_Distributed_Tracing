#include <utility>

#include "model/person.hpp"

namespace lib::model {
person::person(std::string name, std::string title, std::string description)
  : name_(std::move(name)),
    title_(std::move(title)),
    description_(std::move(description)) {
  // nop
}

const std::string& person::name() const noexcept {
  return name_;
}

const std::string& person::title() const noexcept {
  return title_;
}

const std::string& person::description() const noexcept {
  return description_;
}
} // namespace lib::model
