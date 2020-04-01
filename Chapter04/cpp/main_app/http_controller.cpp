#include <tl/expected.hpp>

#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>

#include <jaegertracing/Tracer.h>

#include "http_controller.hpp"
#include "model/person.hpp"

namespace e4 {
namespace {
tl::expected<model::person, std::string>
get_person(const opentracing::SpanContext* ctx, std::string&& name) {
  auto http_client = drogon::HttpClient::newHttpClient("http://localhost:8081");

  auto request = drogon::HttpRequest::newHttpRequest();
  request->setPath("/getPerson/" + std::move(name));

  const std::pair<drogon::ReqResult, drogon::HttpResponsePtr> pair(
    http_client->sendRequest(request));

  const auto& [req_result, http_response_ptr] = pair;

  if (req_result == drogon::ReqResult::Ok) {
    const auto body_string = http_response_ptr->getBody();
    const model::person person(model::person::from_json(body_string));

    return person;
  } else {
    return tl::unexpected("Request to /getPerson failed!");
  }
}

tl::optional<std::string> format_greeting(const opentracing::SpanContext* ctx,
                                          const model::person& person) {
  auto http_client = drogon::HttpClient::newHttpClient("http://localhost:8082");

  auto request = drogon::HttpRequest::newHttpRequest();
  request->setPath("/formatGreeting");
  request->setBody("{\n"
                   "\"name\": "
                   + person.name()
                   + ",\n"
                     "\"title\": "
                   + person.title()
                   + ",\n"
                     "\"description\": "
                   + person.description()
                   + "\n"
                     "}");

  const std::pair<drogon::ReqResult, drogon::HttpResponsePtr> pair(
    http_client->sendRequest(request));

  const auto& [req_result, http_response_ptr] = pair;

  if (req_result == drogon::ReqResult::Ok) {
    const std::string greeting_result(http_response_ptr->getBody());

    return greeting_result;
  } else {
    return tl::nullopt;
  }
}

std::string say_hello(const opentracing::SpanContext* ctx, std::string&& name) {
  const auto exp_person = get_person(ctx, std::move(name));

  if (exp_person.has_value()) {
    const auto opt_greeting = format_greeting(ctx, person);

    if (opt_greeting.has_value()) {
      return *opt_greeting;
    } else {
      return "ERROR: Request to /formatGreeting failed";
    }
  } else {
    return "ERROR: " + exp_person.error();
  }
}
} // namespace

http_controller::http_controller() {
}

void http_controller::handle_say_hello(
  const drogon::HttpRequestPtr& req,
  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
  std::string&& name) {
  auto span = opentracing::Tracer::Global()->StartSpan("say-hello");
  auto resp = drogon::HttpResponse::newHttpResponse();

  auto greeting = say_hello(&span->context(), std::move(name));

  std::string_view sv = greeting;

  if (sv.starts_with("ERROR")) {
    span->SetTag("error", true);
    span->SetTag("errorMessage", greeting);

    resp->setStatusCode(drogon::k500InternalServerError);
    resp->setBody(greeting);
    callback(resp);
    return;
  }

  span->SetTag("response", greeting);

  resp->setStatusCode(drogon::k200OK);
  resp->setBody(greeting);
  callback(resp);
}
} // namespace e4
