#ifndef RANG_TERM_MANIP_HPP_
#define RANG_TERM_MANIP_HPP_

#include "term/terminal.hpp"
#include "term/window.hpp"

namespace term::manip {

namespace raw {
constexpr std::string hl(bool flag) {
  return (flag ? "h" : "l");
}

const std::string esc = "\x1b";
}  // namespace raw

struct clear {};

term::terminal_stream& operator<<(term::terminal_stream&, const clear&);

term::window_stream& operator<<(term::window_stream&, const clear&);
// const std::string clear = raw::esc + "[2J";

struct alternate_buffer {
    bool enable;
};

term::terminal_stream& operator<<(term::terminal_stream&, const alternate_buffer&);

struct cursor {
    bool show;
};

term::terminal_stream& operator<<(term::terminal_stream&, const cursor&);

struct move {
    int x;
    int y;
};

term::terminal_stream& operator<<(term::terminal_stream&, const move&);

term::window_stream& operator<<(term::window_stream&, const move&);

std::string true_color(bool background, uint8_t r, uint8_t g, uint8_t b);

const std::string reset_color = raw::esc + "[0m";

}  // namespace term::manip

#endif  // RANG_TERM_MODIFIERS_HPP_
