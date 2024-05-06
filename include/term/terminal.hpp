#ifndef RANG_TERM_TERMINAL_HPP_
#define RANG_TERM_TERMINAL_HPP_

#include <ostream>

namespace term {

namespace ios {
#include <termios.h>
}

class terminal_stream {
  private:
    std::ostream& raw;

  public:
    terminal_stream(std::ostream& raw);

    template <typename T>
    terminal_stream& operator<<(const T& x) {
      raw << x;
      return *this;
    }

    terminal_stream& operator<<(std::ostream& (*func)(std::ostream&));
};

class terminal {
  private:
    static int m_width;
    static int m_height;

    ios::termios initial_ios;

    static void resize(int);

  public:
    terminal_stream stream;

    terminal();

    terminal(const terminal& other) = delete;

    ~terminal();

    int width() const;

    int height() const;
};

}  // namespace term

#endif  // RANG_TERM_TERMINAL_HPP_
