#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

#include "model/person.hpp"

namespace e5 {
/**
 * The HTTP controller type for the formatter_service.
 */
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  http_controller();

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_format_greeting, "/formatGreeting",
                  drogon::Post);
  METHOD_LIST_END

private:
  /**
   * Handles /formatGreeting requests.
   * @param req The HTTP request.
   * @param callback Callback function.
   * @param person The person that was sent as a JSON object string in the body
   *               of the request.
   */
  void handle_format_greeting(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    model::person&& person) const;
};
} // namespace e5
