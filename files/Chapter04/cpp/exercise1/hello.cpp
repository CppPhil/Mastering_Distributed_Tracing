#include <drogon/drogon.h>

#include "hello.hpp"
#include "people/repository.hpp"
#include "say_hello_http_controller.hpp"

namespace e1 {
void entry_point() {
  const people::repository repo;

  drogon::app().addListener("127.0.0.1", 8080);

  auto http_controller = std::make_shared<say_hello_http_controller>(repo);

  drogon::app().registerController(http_controller);
  drogon::app().run();
}
} // namespace e1
