#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "people/repository.hpp"
#include "tracing/init.hpp"

/**
 * Entry point for the bigbrother_service.
 * @return The exit code.
 */
int main() {
  tracing::init("cpp-5-bigbrother");

  const e5::people::repository repo;

  drogon::app().addListener("localhost", 8081);

  auto http_controller = std::make_shared<e5::http_controller>();
  http_controller->set_repo(repo);

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
