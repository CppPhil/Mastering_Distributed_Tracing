#include "lib/tracing/init.hpp"

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;

  lib::tracing::init("TEST TEXT SERVICE NAME HERE");
}
