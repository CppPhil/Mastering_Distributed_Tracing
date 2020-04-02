#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>

#include <jaegertracing/Tracer.h>

#include "http_controller.hpp"
#include "model/person.hpp"
#include "util/error.hpp"

namespace e4 {
namespace {
tl::expected<model::person, util::error>
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
    return UTIL_UNEXPECTED("Request to /getPerson failed!");
  }
}

tl::expected<std::string, util::error>
format_greeting(const opentracing::SpanContext* ctx,
                const model::person& person) {
  auto http_client = drogon::HttpClient::newHttpClient("http://localhost:8082");

  auto request = drogon::HttpRequest::newHttpRequest();
  request->setPath("/formatGreeting");
  request->setMethod(drogon::Post);
  request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
  request->setBody(person.to_json());

  const std::pair<drogon::ReqResult, drogon::HttpResponsePtr> pair(
    http_client->sendRequest(request));

  const auto& [req_result, http_response_ptr] = pair;

  if (req_result == drogon::ReqResult::Ok) {
    const std::string greeting_result(http_response_ptr->getBody());

    return greeting_result;
  } else {
    return UTIL_UNEXPECTED("Request to /formatGreeting failed!");
  }
}

tl::expected<std::string, util::error>
say_hello(const opentracing::SpanContext* ctx, std::string&& name) {
  const auto exp_person = get_person(ctx, std::move(name));

  if (exp_person.has_value()) {
    const auto exp_greeting = format_greeting(ctx, *exp_person);

    if (exp_greeting.has_value()) {
      return *exp_greeting;
    } else {
      return tl::make_unexpected(exp_greeting.error());
    }
  } else {
    return tl::make_unexpected(exp_person.error());
  }
}
} // namespace

http_controller::http_controller() {
}

void http_controller::handle_say_hello(
  const drogon::HttpRequestPtr& req,
  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
  std::string&& name) const {
  // TODO: HERE

  auto span = opentracing::Tracer::Global()->StartSpan("say-hello");
  auto resp = drogon::HttpResponse::newHttpResponse();

  auto exp_greeting = say_hello(&span->context(), std::move(name));

  if (!exp_greeting.has_value()) {
    span->SetTag("error", true);
    span->SetTag("errorMessage", exp_greeting.error().message());

    resp->setStatusCode(drogon::k500InternalServerError);
    resp->setBody(exp_greeting.error().message());
    callback(resp);
    return;
  }

  span->SetTag("response", *exp_greeting);

  resp->setStatusCode(drogon::k200OK);
  resp->setBody(*exp_greeting);
  callback(resp);
}
} // namespace e4
