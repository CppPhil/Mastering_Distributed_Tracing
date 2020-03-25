#include <string>
#include <tuple>
#include <vector>

#include <Poco/Data/Statement.h>

#include "repository.hpp"

namespace e1::people {
const std::string conn_info
  = "host=127.0.0.1 port=3306 dbname=chapter04 user=root password=mysqlpwd";

repository::repository()
  : connector_(), session_(connector_.createSession(conn_info)) {
}

repository::~repository() = default;

model::person repository::get_person(std::string_view name) const {
  /*
constexpr std::string_view query
  = "select title, description from people where name = ?";

const drogon::orm::Result result
  = db_client_->execSqlSync(std::string(query.begin(), query.end()),
                            std::string(name.begin(), name.end()));

for (const drogon::orm::Row& row : result) {
  const drogon::orm::Field title = row["title"];
  const drogon::orm::Field description = row["description"];

  return model::person(std::string(name.begin(), name.end()), title.c_str(),
                       description.c_str());
}

return model::person(std::string(name.begin(), name.end()), "", "");
*/

  using namespace Poco::Data::Keywords;

  std::vector<std::tuple<std::string, std::string>> v;
  Poco::Data::Statement select(session_);
  select << "select title, description from people where name = ?", into(v),
    use(std::string(name.begin(), name.end())), now;

  for (const auto& [title, descr] : v) {
    return model::person(std::string(name.begin(), name.end()), title, descr);
  }

  return model::person(std::string(name.begin(), name.end()), "", "");
}
} // namespace e1::people
