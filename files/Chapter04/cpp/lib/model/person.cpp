#include <utility>

#include "model/person.hpp"

namespace lib::model {
Person::Person(std::string name, std::string title, std::string description)
  : name_(std::move(name)),
    title_(std::move(title)),
    description_(std::move(description))
{
  // nop
}

const std::string& Person::name() const noexcept
{
  return name_;
}

const std::string& Person::title() const noexcept
{
  return title_;
}

const std::string& Person::description() const noexcept {
  return description_;
}
} // namespace lib::model
