#include "http_controller.hpp"
#include "format_greeting.hpp"
#include "tracing/create_span.hpp"
#include "tracing/extract.hpp"

namespace e4 {
http_controller::http_controller() {
}

void http_controller::handle_format_greeting(
  const drogon::HttpRequestPtr& req,
  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
  model::person&& person) const {
  auto ctx = tracing::extract(*req);
  auto span = tracing::create_span(ctx, "/formatGreeting");
  span->SetTag("span.kind", "server");
  auto resp = drogon::HttpResponse::newHttpResponse();
  const auto greeting = format_greeting(person.name(), person.title(),
                                        person.description(), &span->context());
  resp->setStatusCode(drogon::k200OK);
  resp->setBody(greeting);
  callback(resp);
}
} // namespace e4
