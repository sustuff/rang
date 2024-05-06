#ifndef RANG_TERM_WINDOW_HPP_
#define RANG_TERM_WINDOW_HPP_

#include "term/terminal.hpp"

namespace term {

struct window_dimensions {
    int offset_x{};
    int offset_y{};
    int size_x{};
    int size_y{};
};

class window_stream {
  private:
    terminal_stream& raw;

  public:
    const window_dimensions& dimensions;

    window_stream(terminal_stream& term, const window_dimensions& dim);

    template <typename T>
    window_stream& operator<<(const T& x) {
      raw << x;
      return *this;
    }

    window_stream& operator<<(std::ostream& (*func)(std::ostream&));
};

class window {
  private:
    window_dimensions dimensions;

  public:
    window_stream stream;

    window(terminal& term, const window_dimensions& dim);

    void change_dimensions(const window_dimensions& dim);
};
}  // namespace term

#endif  // RANG_TERM_WINDOW_HPP_
