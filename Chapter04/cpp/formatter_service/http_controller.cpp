#include "http_controller.hpp"
#include "format_greeting.hpp"

namespace e4 
{
http_controller::http_controller()
{
}

void http_controller::handle_format_greeting(
  const drogon::HttpRequestPtr& req,
  std::function<void (const drogon::HttpResponsePtr&)> &&callback,
  model::person&& person
)
{ 
  auto span = opentracing::Tracer::Global()->StartSpan("/formatGreeting");
  auto resp = drogon::HttpResponse::newHttpResponse();
  
  const auto greeting = format_greeting(
    person.name(), person.title(), person.description(),
    &span->context()  
  );
  
  resp->setStatusCode(drogon::k200OK);
  resp->setBody(greeting);
  callback(resp);
}
} // namespace e4

