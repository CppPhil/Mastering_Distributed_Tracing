#include <jaegertracing/Tracer.h>
#include <sstream>

#include "http_controller.hpp"
#include "people/repository.hpp"
#include "tracing/extract.hpp"

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
  tl::expected<std::unique_ptr<opentracing::SpanContext>, util::error> ctx(
    tracing::extract(*req));

  auto span = (!ctx.has_value() || *ctx == nullptr)
                ? opentracing::Tracer::Global()->StartSpan("/getPerson")
                : opentracing::Tracer::Global()->StartSpan(
                  "/getPerson", {opentracing::ChildOf(ctx->get())});
  auto resp = drogon::HttpResponse::newHttpResponse();

  const auto person = repo_->get_person(std::move(name), &span->context());

  span->Log({{"name", person.name()},
             {"title", person.title()},
             {"description", person.description()}});

  resp->setStatusCode(drogon::k200OK);
  resp->setBody(person.to_json());
  callback(resp);
}
} // namespace e4
