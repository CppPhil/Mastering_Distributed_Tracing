#pragma once
#include <drogon/HttpController.h>

#include <pl/noncopyable.hpp>

namespace e4 {
class http_controller : public drogon::HttpController<http_controller, false> {
public:
  PL_NONCOPYABLE(http_controller);

  http_controller();

  METHOD_LIST_BEGIN
    ADD_METHOD_TO(http_controller::handle_TODO_HERE, "/TODO HERE", drogon::Get);
    METHO_LIST_END

  private:
};
} // namespace e4
