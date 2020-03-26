#include <cstdio>

#include <Poco/Data/MySQL/MySQLException.h>

#include "hello.hpp"
#include "people/repository.hpp"

namespace e1 {
void entry_point() {
  try {
    fprintf(stderr, "About to create repo\n");
    const people::repository repo;
    fprintf(stderr, "Created repo\n");

    fprintf(stderr, "About to call get_person\n");
    const model::person result_value(repo.get_person("Gru"));
    fprintf(stderr, "Finished calling get_person\n");

    printf("Result: \"model::person{\"name\": \"%s\", \"title\": \"%s\", "
           "\"description\": \"%s\"}\"\n",
           result_value.name().c_str(), result_value.title().c_str(),
           result_value.description().c_str());

  } catch (const Poco::Data::MySQL::MySQLException& ex) {
    fprintf(stderr, "Caught MySQLException: %s\n", ex.what());
  }
  // TODO: Implement HTTP server
}
} // namespace e1
