#include "term/terminal.hpp"
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include "term/modifiers.hpp"

namespace term {
using namespace modifiers;

terminal::terminal() {
  // disable echo and buffering
  tcgetattr(fileno(stdout), &initial_ios);
  ios::termios current = initial_ios;
  current.c_lflag &= (~ECHO & ~ICANON);
  tcsetattr(fileno(stdout), TCSANOW, &current);

  // set initial terminal size
  terminal::resize(0);

  // handle terminal resize
  signal(SIGWINCH, terminal::resize);

  std::cout << alternate_buffer(true) << clear << cursor(false) << std::flush;
}

terminal::~terminal() {
  std::cout << clear << alternate_buffer(false) << cursor(true) << std::flush;

  // restore termios
  tcsetattr(fileno(stdout), TCSANOW, &initial_ios);
}

int terminal::width;
int terminal::height;

void terminal::resize(int) {
  winsize ws;
  ioctl(1, TIOCGWINSZ, &ws);
  terminal::width = ws.ws_col;
  terminal::height = ws.ws_row;
}
}  // namespace term
