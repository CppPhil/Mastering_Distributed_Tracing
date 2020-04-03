#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "tracing/init.hpp"

/**
 * Entry point for the formatter service.
 * @return The exit code.
 */
int main() {
  tracing::init("cpp-5-formatter");

  drogon::app().addListener("localhost", 8082);

  auto http_controller = std::make_shared<e5::http_controller>();

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
