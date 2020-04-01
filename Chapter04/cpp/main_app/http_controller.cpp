#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>

#include <jaegertracing/Tracer.h>

#include "http_controller.hpp"
#include "model/person.hpp"

namespace e4 {
namespace {
model::person get_person(const opentracing::SpanContext* ctx,
                         std::string&& name) {
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
    // TODO: Handle error.
  }
}

std::string format_greeting(const opentracing::SpanContext* ctx,
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
    // TODO: Handle error.
  }
}

std::string say_hello(const opentracing::SpanContext* ctx, std::string&& name) {
  const auto person = get_person(http_client, ctx, std::move(name));

  return format_greeting(ctx, person);
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

  span->SetTag("response", greeting);

  resp->setStatusCode(drogon::k200OK);
  resp->setBody(greeting);
  callback(resp);
}
} // namespace e4
