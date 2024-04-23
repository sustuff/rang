#include "term/terminal.hpp"
#include "term/manip.hpp"

#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>

namespace term {
terminal_stream::terminal_stream(std::ostream& raw) : raw(raw) {
}

terminal_stream& terminal_stream::operator<<(std::ostream& (*func)(std::ostream&)) {
  raw << func;
  return *this;
}

terminal::terminal() : stream(std::cout) {
  // disable echo and buffering
  tcgetattr(fileno(stdout), &initial_ios);
  ios::termios current = initial_ios;
  current.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(fileno(stdout), TCSANOW, &current);

  // set initial terminal size
  terminal::resize(0);

  // handle terminal resize
  signal(SIGWINCH, terminal::resize);

  stream << manip::alternate_buffer{true} << manip::clear{} << manip::cursor{false} << std::flush;
}

terminal::~terminal() {
  stream << manip::clear{} << manip::alternate_buffer{false} << manip::cursor{true} << std::flush;

  // restore termios
  tcsetattr(fileno(stdout), TCSANOW, &initial_ios);
}

int terminal::m_width;
int terminal::m_height;

int terminal::width() const {
  return m_width;
}

int terminal::height() const {
  return m_height;
}

void terminal::resize(int) {
  winsize ws;
  ioctl(1, TIOCGWINSZ, &ws);
  terminal::m_width = ws.ws_col;
  terminal::m_height = ws.ws_row;
}

}  // namespace term
