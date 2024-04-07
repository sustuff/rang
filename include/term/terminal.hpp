#ifndef RANG_TERMINAL_HPP_
#define RANG_TERMINAL_HPP_

namespace term {

namespace ios {
#include <termios.h>
}

class terminal {
  private:
    static int m_width;
    static int m_height;

    ios::termios initial_ios;

    static void resize(int);

  public:
    terminal();

    terminal(const terminal& other) = delete;

    ~terminal();

    int width() const;

    int height() const;

    operator std::ostream&() const;
};

}  // namespace term

#endif  // RANG_TERMINAL_HPP_
