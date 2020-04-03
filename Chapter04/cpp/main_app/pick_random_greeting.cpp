#include <cstddef>

#include <pl/cont/make_array.hpp>
#include <pl/random_number_generator.hpp>

#include "pick_random_greeting.hpp"

namespace e4 {
const std::string& pick_random_greeting() {
  using namespace std::string_literals;
  thread_local pl::random_number_generator<std::mt19937_64> rng;
  static const auto greetings = pl::cont::make_array("Hi"s, "Howdy"s, "G'day"s);

  return greetings[rng.generate<size_t>(0U, greetings.size() - 1U)];
}
} // namespace e4