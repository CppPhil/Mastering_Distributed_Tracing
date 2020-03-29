#pragma once
#include <optional>
#include <string>

#include <tl/optional.hpp>

#include <Poco/Data/Session.h>

#include "model/person.hpp"

namespace e1::people {
class repository {
public:
  repository();

  repository(const repository&) = delete;

  repository& operator=(const repository&) = delete;

  ~repository();

  tl::optional<model::person> get_person(std::string name) const;

private:
  mutable std::optional<Poco::Data::Session> session_;
};
} // namespace e1::people
