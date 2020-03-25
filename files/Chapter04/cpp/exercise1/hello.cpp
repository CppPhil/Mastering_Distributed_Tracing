#include "hello.hpp"
#include "people/repository.hpp"

namespace e1 {
void entry_point() {
  const people::repository repo;

  const model::person result_value(repo.get_person("Gru"));

  // TODO: Implement HTTP server
}
} // namespace e1
