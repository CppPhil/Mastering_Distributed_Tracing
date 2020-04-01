#include <sstream>

//#include <Poco/JSON/Object.h>

#include <jaegertracing/Tracer.h>

#include "http_controller.hpp"
#include "people/repository.hpp"

namespace e4 {
http_controller::http_controller() : repo_(nullptr) {
}

void http_controller::set_repo(const people::repository& repo) {
  repo_ = &repo;
}

void http_controller::handle_get_person(
  const drogon::HttpRequestPtr& req,
  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
  std::string&& name) {
  auto span = opentracing::Tracer::Global()->StartSpan("/getPerson");

  const auto opt_person = repo_->get_person(std::move(name), span->Context());

  if (opt_person.has_value()) {
    const auto& person = *opt_person;
    span->Log({{"name", person.name()},
               {"title", person.title()},
               {"description", person.description()}});

    /*
    const auto obj = Poco::JSON::Object{}
                       .set("name", person.name())
                       .set("title", person.title())
                       .set("desciption", person.description());
    std::ostringstream oss;
    obj.stringify(oss);
    const auto json = obj.str(); */

    const std::string json = "FOTZE";

    resp->setStatusCode(drogon::k200OK);
    resp->setBody(json);
    callback(resp);
  } else {
    span->SetTag("error", true);
    span->Log({{"error", "database access failed"}});
    resp->setStatusCode(drogon::k500InternalServerError);
    callback(resp);
  }
}
} // namespace e4
