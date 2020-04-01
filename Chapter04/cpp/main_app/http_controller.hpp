#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e4 {
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  http_controller();

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_say_hello, "/sayHello/{name}",
                  drogon::Get);
  METHOD_LIST_END

private:
  void handle_say_hello(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name) const;
};
} // namespace e4
