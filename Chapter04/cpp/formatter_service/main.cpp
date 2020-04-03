#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "tracing/init.hpp"

int main() {
  tracing::init("cpp-5-formatter");

  drogon::app().addListener("localhost", 8082);

  auto http_controller = std::make_shared<e4::http_controller>();

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
