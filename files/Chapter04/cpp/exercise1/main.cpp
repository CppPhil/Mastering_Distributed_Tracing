#include "tracing/init.hpp"

int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;

  tracing::init("TEST TEXT SERVICE NAME HERE");
}
