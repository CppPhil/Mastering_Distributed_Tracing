#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e4 {
namespace people {
class repository;
} // namespace people

class http_controller
{
public:
  PL_NONCOPYABLE(http_controller)

  http_controller();

  void set_repo(const people::repository& repo);

  // TODO: See if the stuff below can be private.

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_get_person, "/getPerson/{name}", drogon::Get);
  METHOD_LIST_END

  void handle_get_person(
    const drogon::HttpRequestPtr& req,
    std::function<void (const drogon::HttpResponsePtr&)>&& callback,
    std::string&& name);

private:
  const people::repository* repo_;
};
} // namespace e4

