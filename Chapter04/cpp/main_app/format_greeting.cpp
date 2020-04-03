#include <drogon/HttpRequest.h>

#include "format_greeting.hpp"
#include "pick_random_greeting.hpp"
#include "send_request.hpp"

namespace e5 {
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
} // namespace e5
