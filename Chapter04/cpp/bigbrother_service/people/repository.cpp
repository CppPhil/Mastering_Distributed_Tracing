#include <mutex>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Statement.h>

#include "repository.hpp"

namespace e5::people {
const std::string conn_info = "host=127.0.0.1;port=3306;user=phillip;password="
                              "mysqlpwd;auto-reconnect=true;db=chapter04";

std::once_flag register_mysql_connector_once;

repository::repository() : session_(std::nullopt) {
  std::call_once(register_mysql_connector_once,
                 &Poco::Data::MySQL::Connector::registerConnector);

  session_ = Poco::Data::Session("MySQL", conn_info);
}

repository::~repository() = default;

model::person
repository::get_person(std::string name,
                       const opentracing::SpanContext* ctx) const {
  using namespace Poco::Data::Keywords;

  const char* const query
    = "select title, description from people where name = ?";

  auto span = opentracing::Tracer::Global()->StartSpan(
    "get-person", {opentracing::ChildOf(ctx)});
  span->SetTag("db.statement", query);

  std::string title;
  std::string description;
  Poco::Data::Statement select(*session_);
  select << query, use(name), into(title), into(description), range(0, 1);

  while (!select.done()) {
    select.execute();
    return model::person(name, title, description);
  }

  return model::person(name, "", "");
}
} // namespace e5::people
