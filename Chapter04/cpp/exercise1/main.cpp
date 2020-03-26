#include "hello.hpp"
#include "tracing/init.hpp"

int main() {
  tracing::init("cpp-exercise1");

  e1::entry_point();
}
