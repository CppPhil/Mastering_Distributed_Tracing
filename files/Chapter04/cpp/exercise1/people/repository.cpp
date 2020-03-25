#include <tuple>
#include <vector>

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

  std::vector<std::tuple<std::string, std::string>> v;
  Poco::Data::Statement select(session_);
  select << "select title, description from people where name = ?", into(v),
    use(name), now;

  for (const auto& [title, descr] : v)
    return model::person(name, title, descr);

  return model::person(name, "", "");
}
} // namespace e1::people
