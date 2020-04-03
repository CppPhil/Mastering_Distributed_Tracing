#include <utility>

#include <drogon/HttpRequest.h>

#include "get_person.hpp"
#include "send_request.hpp"

namespace e5 {
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
} // namespace e5
