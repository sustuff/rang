#ifndef RANG_TERMINAL_HPP_
#define RANG_TERMINAL_HPP_

namespace term {

namespace ios {
#include <termios.h>
}

class terminal {
    static int width;
    static int height;

    ios::termios initial_ios;

  private:
    static void resize(int);

    void init();

  public:
    terminal();

    terminal(const terminal& other) = delete;

    ~terminal();
};

}  // namespace term

#endif  // RANG_TERMINAL_HPP_
