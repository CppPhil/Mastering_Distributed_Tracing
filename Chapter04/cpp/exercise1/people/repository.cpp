#include <mutex>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Statement.h>

#include "repository.hpp"

namespace e1::people {
const std::string conn_info = "host=127.0.0.1;port=3306;user=phillip;password="
                              "mysqlpwd;auto-reconnect=true;db=chapter04";

std::once_flag register_mysql_connector_once;

repository::repository() : session_(std::nullopt) {
  std::call_once(register_mysql_connector_once,
                 &Poco::Data::MySQL::Connector::registerConnector);

  session_ = Poco::Data::Session("MySQL", conn_info);
}

repository::~repository() = default;

tl::optional<model::person>
repository::get_person(std::string name, opentracing::Span& parent_span) const {
  using namespace Poco::Data::Keywords;

  const char* const query
    = "select title, description from people where name = ?";

  auto span = opentracing::Tracer::Global()->StartSpan(
    "get-person", {opentracing::ChildOf(&parent_span.context())});
  span->SetTag("db.statement", query);

  std::string title;
  std::string description;
  Poco::Data::Statement select(*session_);
  select << query, use(name), into(title), into(description), range(0, 1);

  while (!select.done()) {
    if (select.execute() == 0)
      return tl::nullopt;
    else
      return model::person(name, title, description);
  }

  return model::person(name, "", "");
}
} // namespace e1::people
