#include <vector>

#include <cstdio>

#include <Poco/Data/Statement.h>

#include "repository.hpp"

namespace e1::people {
const std::string conn_info
  = "host=127.0.0.1 port=3306 dbname=chapter04 user=root password=mysqlpwd";

repository::repository()
  : connector_(), session_(connector_.createSession(conn_info)) {
  // nop
}

repository::~repository() = default;

model::person repository::get_person(std::string name) const {
  using namespace Poco::Data::Keywords;

  std::vector<std::string> v;
  Poco::Data::Statement select(session_);
  select << "select title, description from people where name = ?", name,
    into(v), now;

  for (const auto& element : v) {
    fprintf(stderr, "ELEMENT: \"%s\"!\n", element.c_str());

    // TODO: ACTUALLY PUT THE REAL TITLE AND DESCRIPTION IN THERE
    return model::person(name, "title", "descr");
  }

  return model::person(name, "", "");
}
} // namespace e1::people
