#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "tracing/init.hpp"

int main() {
  tracing::init("TODO HERE");

  drogon::app().addListener("localhost", TODO PORT HERE);

  auto http_controller = std::make_shared<e4::http_controller>();

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
