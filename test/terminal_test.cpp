#include "term/terminal.hpp"
#include <unistd.h>
#include <catch2/catch_all.hpp>
#include <iostream>
#include "term/modifiers.hpp"

TEST_CASE("simple terminal") {
  term::terminal term;

  using namespace term::modifiers;
  std::cout << move(0, 0) << true_color(false, 255, 0, 0) << "Hello, world!" << reset_color
            << std::flush;
  sleep(1);
}
