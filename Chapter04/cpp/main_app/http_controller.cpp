#include <array>
#include <string>

#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>

#include <jaegertracing/Tracer.h>

#include <pl/cont/make_array.hpp>
#include <pl/random_number_generator.hpp>

#include "http_controller.hpp"
#include "model/person.hpp"
#include "tracing/create_span.hpp"
#include "tracing/extract.hpp"
#include "tracing/inject.hpp"
#include "util/error.hpp"

namespace e4 {
namespace {
std::pair<drogon::ReqResult, drogon::HttpResponsePtr>
send_request(const opentracing::SpanContext* ctx,
             const std::string& operation_name, const std::string& host,
             const std::string& path, drogon::HttpRequestPtr& http_request) {
  auto http_client = drogon::HttpClient::newHttpClient(host);
  http_request->setPath(path);

  auto span = opentracing::Tracer::Global()->StartSpan(
    operation_name, {opentracing::ChildOf(ctx)});
  span->SetTag("span.kind", "client");
  span->SetTag("http.url", host + path);
  span->SetTag("http.method", http_request->getMethodString());

  const char* const body_data = http_request->bodyData();
  const size_t body_length = http_request->bodyLength();
  const std::string buf(body_data, body_length);
  span->SetTag("request.body", buf);

  tracing::inject(*http_request, span->context());

  return http_client->sendRequest(http_request);
}

tl::expected<model::person, util::error>
get_person(const opentracing::SpanContext* ctx, std::string&& name) {
  auto request = drogon::HttpRequest::newHttpRequest();
  const std::pair<drogon::ReqResult, drogon::HttpResponsePtr> pair(send_request(
    /* ctx */ ctx,
    /* operation_name */ "getPerson",
    /* host */ "http://localhost:8081",
    /* path */ "/getPerson/" + std::move(name),
    /* http_request */ request));

  const auto& [req_result, http_response_ptr] = pair;

  if (req_result == drogon::ReqResult::Ok) {
    const auto body_string = http_response_ptr->getBody();
    const model::person person(model::person::from_json(body_string));

    return person;
  } else {
    return UTIL_UNEXPECTED("Request to /getPerson failed!");
  }
}

const std::string& pick_random_greeting() {
  using namespace std::string_literals;
  thread_local pl::random_number_generator<std::mt19937_64> rng;
  static const auto greetings = pl::cont::make_array("Hi"s, "Howdy"s, "G'day"s);

  return greetings[rng.generate<size_t>(0U, greetings.size() - 1U)];
}

tl::expected<std::string, util::error>
format_greeting(opentracing::Span& span, const model::person& person) {
  auto request = drogon::HttpRequest::newHttpRequest();
  request->setMethod(drogon::Post);
  request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
  request->setBody(person.to_json());

  span.SetBaggageItem("greeting", pick_random_greeting());

  const std::pair<drogon::ReqResult, drogon::HttpResponsePtr> pair(send_request(
    /* ctx */ &span.context(),
    /* operation_name */ "formatGreeting",
    /* host */ "http://localhost:8082",
    /* path */ "/formatGreeting",
    /* http_request */ request));

  const auto& [req_result, http_response_ptr] = pair;

  if (req_result == drogon::ReqResult::Ok) {
    const std::string greeting_result(http_response_ptr->getBody());

    return greeting_result;
  } else {
    return UTIL_UNEXPECTED("Request to /formatGreeting failed!");
  }
}

tl::expected<std::string, util::error> say_hello(opentracing::Span& span,
                                                 std::string&& name) {
  const auto exp_person = get_person(&span.context(), std::move(name));

  if (exp_person.has_value()) {
    const auto exp_greeting = format_greeting(span, *exp_person);

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
  auto span_context = tracing::extract(*req);
  auto span = tracing::create_span(span_context, "say-hello");
  span->SetTag("span.kind", "server");
  auto resp = drogon::HttpResponse::newHttpResponse();
  auto exp_greeting = say_hello(*span, std::move(name));

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
