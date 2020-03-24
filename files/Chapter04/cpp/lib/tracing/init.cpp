#include <cstdio>

#include "tracing/init.hpp"

namespace tracing {
void init(const std::string& service) {
  fprintf(stderr,
          "DUMMY IMPLEMENTATION\nlib::tracing::init called with: \"%s\"\n",
          service.c_str());
}
} // namespace tracing
