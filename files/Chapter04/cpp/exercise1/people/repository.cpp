#include "repository.hpp"

#if 0
namespace e1::people {
constexpr std::string_view conn_info
  = "host=127.0.0.1 port=3306 dbname=chapter04 user=root password=mysqlpwd";

repository::repository()
  : db_client_(drogon::orm::DbClient::newMysqlClient(
    std::string(conn_info.begin(), conn_info.end()), /* connNum */ 1)) {
  // nop
}

repository::~repository() = default;

model::person repository::get_person(std::string_view name) const {
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
}
} // namespace e1::people
#endif /* 0 */
