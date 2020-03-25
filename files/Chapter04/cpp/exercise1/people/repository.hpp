#pragma once
#include <string_view>

#include "model/person.hpp"

namespace e1::people {
class repository {
public:
  repository();

  repository(const repository&) = delete;

  repository& operator=(const repository&) = delete;

  ~repository();

  model::person get_person(std::string_view name) const;

private:
  // drogon::orm::DbClientPtr db_client_;
};
} // namespace e1::people
