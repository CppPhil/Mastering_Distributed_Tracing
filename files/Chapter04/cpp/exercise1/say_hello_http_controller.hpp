#pragma once
#include <drogon/HttpController.h>

#include "people/repository.hpp"

namespace e1 {
class say_hello_http_controller
  : public drogon::HttpController<say_hello_http_controller, false> {
public:
  say_hello_http_controller();

  say_hello_http_controller(const say_hello_http_controller&) = delete;

  say_hello_http_controller& operator=(const say_hello_http_controller&)
    = delete;

  void set_repo(const people::repository& repo);

  METHOD_LIST_BEGIN
    METHOD_ADD(say_hello_http_controller::handle_say_hello, "/sayHello/{name}",
               drogon::Get);
  METHOD_LIST_END

  void handle_say_hello(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name);

private:
  const people::repository* repo_;
};
} // namespace e1
