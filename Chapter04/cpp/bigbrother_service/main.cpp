#include <drogon/drogon.h>

#include "http_controller.hpp"
#include "people/repository.hpp"
#include "tracing/init.hpp"

int main() {
  tracing::init("cpp-4-bigbrother");

  const e4::people::repository repo;

  drogon::app().addListener("localhost", 8081);

  auto http_controller = std::make_shared<e4::http_controller>();
  http_controller->set_repo(repo);

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
