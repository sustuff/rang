#include <unistd.h>
#include <catch2/catch_all.hpp>
#include "ncurses/base.hpp"

std::shared_ptr<ncurses::base_window> base;

class testRunListener : public Catch::EventListenerBase {
  public:
    using Catch::EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const&) override {
      base = std::make_shared<ncurses::base_window>();
    }
};

CATCH_REGISTER_LISTENER(testRunListener)

TEST_CASE("ncurses test") {
  base->refresh();

  SECTION("output test") {
    base->output("Hello!");
    base->refresh();
    base->move_caret(0, 0);

    char buffer[10];
    ncurses::impl::winnstr(ncurses::impl::stdscr, buffer, 6);
    REQUIRE(std::string(buffer) == "Hello!");
  }

  SECTION("subwindow test") {
    auto kek = base->subwindow(10, 10, 1, 1);
    base->refresh();
    kek->refresh();
  }
}
