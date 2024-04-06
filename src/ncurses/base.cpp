#include "ncurses/base.hpp"

namespace ncurses {
base_window::base_window() {
  win_ptr = impl::initscr();
  if (!win_ptr) {
    throw 1;
  }
  size_x = impl::COLS;
  size_y = impl::LINES;
}

base_window::~base_window() {
  impl::endwin();
}
}  // namespace ncurses
