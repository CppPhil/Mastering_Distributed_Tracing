#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e5 {
/**
 * Type for the HTTP controller of the main_app.
 */
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  /**
   * Creates a new http_controller.
   */
  http_controller();

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_say_hello, "/sayHello/{name}",
                  drogon::Get);
  METHOD_LIST_END

private:
  /**
   * Handles "sayHello"-Requests.
   * @param req The incoming HTTP request.
   * @param callback The callback function to 'return' the result to the
   *                 requester.
   * @param name The name of the person to say hello to, given by the requester.
   */
  void handle_say_hello(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name) const;
};
} // namespace e5
