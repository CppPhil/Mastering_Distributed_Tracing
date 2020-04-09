#include <jaegertracing/Tracer.h>

#include "http_controller.hpp"
#include "say_hello.hpp"
#include "tracing/create_span.hpp"
#include "tracing/extract.hpp"

namespace e5 {
http_controller::http_controller() = default;

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
} // namespace e5
