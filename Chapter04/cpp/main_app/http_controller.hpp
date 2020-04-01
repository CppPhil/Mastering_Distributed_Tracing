#pragma once
#include <drogon/HttpClient.h>
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e4 {
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  http_controller();

  // TODO: Check what can be private here.
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_say_hello, "/sayHello{name}",
                  drogon::Get);
  METHOD_LIST_END

  void handle_say_hello(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name);

private:
  drogon::HttpClientPtr http_client_;
};
} // namespace e4
