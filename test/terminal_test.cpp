#include "term/terminal.hpp"
#include <unistd.h>
#include <catch2/catch_all.hpp>
#include <iostream>
#include "term/manip.hpp"

TEST_CASE("simple terminal") {
  term::terminal term;

  using namespace term::manip;
  term.stream << move{1, 1} << true_color(false, 255, 0, 0) << "Hello, world!" << reset_color
              << std::flush;
  sleep(1);
}
