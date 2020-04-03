#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "tracing/init.hpp"

/**
 * Entry point of the application.
 * @return The exit code. A non-zero exit code indicates failure.
 */
int main() {
  tracing::init("cpp-5-hello");

  drogon::app().addListener("localhost", 8080);

  auto http_controller = std::make_shared<e5::http_controller>();

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
