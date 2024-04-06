#include "ncurses/window.hpp"
#include <algorithm>
#include <memory>

namespace ncurses {
window::window(int size_x, int size_y, int offset_x, int offset_y, std::weak_ptr<window> parent)
    : size_x(size_x), size_y(size_y), parent(parent) {
  win_ptr = impl::newwin(size_y, size_x, offset_y, offset_x);
  if (!win_ptr) {
    throw 1;  // TODO errors
  }
  refresh();
}

window::~window() {
  auto parent_ptr = parent.lock();
  subwindows.clear();
  if (parent_ptr) {
    parent_ptr->subwindows.erase(std::find(parent_ptr->subwindows.begin(),
                                           parent_ptr->subwindows.end(),
                                           std::shared_ptr<window>(this)));
  }
  delwin(win_ptr);
}

bool window::operator==(const window& other) const {
  return win_ptr == other.win_ptr;
}

int window::get_size_x() const {
  return size_x;
}

int window::get_size_y() const {
  return size_y;
}

int window::get_offset_x() const {
  return offset_x;
}

int window::get_offset_y() const {
  return offset_y;
}

void window::refresh() const {
  if (impl::wrefresh(win_ptr) == ERR) {
    throw 1;
  };
}

void window::move_caret(int x, int y) const {
  if (impl::wmove(win_ptr, y, x) == ERR) {
    throw 1;
  };
}

void window::output(const std::string& s) const {
  if (impl::waddstr(win_ptr, s.c_str()) == ERR) {
    throw 1;
  }
}

void window::move_caret_and_output(int x, int y, const std::string& s) const {
  move_caret(x, y);
  output(s);
}

void window::output_line(int y, const std::string& s) const {
  auto line = s;
  line.resize(size_x - 1, ' ');
  move_caret_and_output(y, 0, line);
}

std::shared_ptr<window> window::subwindow(int size_x, int size_y, int offset_x, int offset_y) {
  auto result = std::make_shared<window>();
  result->win_ptr = impl::subwin(win_ptr, size_y, size_x, offset_y, offset_x);
  if (!result->win_ptr) {
    throw 1;
  }
  result->size_x = size_x;
  result->size_y = size_y;
  subwindows.push_back(result);
  return result;
}

int window::set_keypad(bool value) const {
  return impl::keypad(win_ptr, (value ? TRUE : FALSE));
}

}  // namespace ncurses
