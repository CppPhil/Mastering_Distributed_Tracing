#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

#include "model/person.hpp"

namespace e4 {
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  http_controller();

  // TODO: Check if some of this can be private.

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_format_greeting, "TODO HERE", 
     drogon::Post);
  METHOD_LIST_END

  void handle_format_greeting(
    const drogon::HttpRequestPtr& req,
    std::function<void (const drogon::HttpResponsePtr&)> &&callback,
    model::person&& person
  ) const;


};
} // namespace e4

