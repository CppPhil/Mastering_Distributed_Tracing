#pragma once
#include <string>

namespace lib::model {
class person
{
public:
  Person(std::string name, std::string title, std::string description);

  const std::string& name() const noexcept;

  const std::string& title() const noexcept;

  const std::string& description() const noexcept;

private:
  std::string name_;
  std::string title_;
  std::string description_;
};
} // namespace lib::model
