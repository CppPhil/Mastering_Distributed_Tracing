#include <jaegertracing/Tracer.h>

#include "say_hello_http_controller.hpp"

namespace e1 {
namespace {
std::string format_greeting(const std::string& name, const std::string& title,
                            const std::string& description) {
  std::string response = "Hello, ";

  if (!title.empty())
    response += title + " ";

  response += name + "!";

  if (!description.empty())
    response += " " + description;

  return response;
}

tl::optional<std::string> say_hello(const people::repository& repo,
                                    std::string&& name,
                                    opentracing::Span& span) {
  const tl::optional<model::person> person(repo.get_person(std::move(name)));

  if (person.has_value()) {
    span.Log({{"name", person->name()},
              {"title", person->title()},
              {"description", person->description()}});

    return format_greeting(person->name(), person->title(),
                           person->description());
  } else
    return tl::nullopt;
}
} // namespace

say_hello_http_controller::say_hello_http_controller() : repo_(nullptr) {
}

void say_hello_http_controller::set_repo(const people::repository& repo) {
  repo_ = &repo;
}

void say_hello_http_controller::handle_say_hello(
  const drogon::HttpRequestPtr& req,
  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
  std::string&& name) {
  auto span = opentracing::Tracer::Global()->StartSpan("say-hello");

  auto resp = drogon::HttpResponse::newHttpResponse();

  tl::optional<std::string> optional_greeting(
    say_hello(*repo_, std::move(name), *span));

  if (optional_greeting.has_value()) {
    std::string& greeting(*optional_greeting);
    span->SetTag("response", greeting);
    resp->setBody(std::move(greeting));
    callback(resp);
  } else {
    span->SetTag("error", true);
    span->Log({{"error", "database access failed"}});

    resp->setStatusCode(drogon::k200OK);
    callback(resp);
  }
}
} // namespace e1
