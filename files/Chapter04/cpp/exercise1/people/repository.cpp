#include <Poco/Data/Statement.h>

#include "repository.hpp"

namespace e1::people {
const std::string conn_info = "host=127.0.0.1;port=3306;user=phillip;password="
                              "mysqlpwd;auto-reconnect=true;dbname=chapter04";

repository::repository()
  : connector_(), session_(connector_.createSession(conn_info)) {
  // nop
}

repository::~repository() = default;

model::person repository::get_person(std::string name) const {
  using namespace Poco::Data::Keywords;

  std::string title;
  std::string description;
  Poco::Data::Statement select(session_);
  select << "select title, description from people where name = ?", use(name),
    into(title), into(description);

  while (!select.done()) {
    select.execute();
    return model::person(name, title, description);
  }

  return model::person(name, "", "");
}
} // namespace e1::people
