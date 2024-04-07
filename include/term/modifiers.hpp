#ifndef RANG_TERM_MODIFIERS_HPP_
#define RANG_TERM_MODIFIERS_HPP_

#include <format>

namespace term::modifiers {

constexpr std::string hl(bool flag) {
  return (flag ? "h" : "l");
}

const std::string esc = "\x1b";

constexpr std::string alternate_buffer(bool enable) {
  return esc + "[?1049" + hl(enable);
}

const std::string clear = esc + "[?1049";

constexpr std::string cursor(bool show) {
  return esc + "[?25" + hl(show);
}

constexpr std::string move(int x, int y) {
  return esc + std::format("[{};{}H", y, x);
}

constexpr std::string true_color(bool background, uint8_t r, uint8_t g, uint8_t b) {
  return esc + std::format("[{};2;{};{};{}m", (background ? 48 : 38), r, g, b);
}

const std::string reset_color = esc + "[0m";

}  // namespace term::modifiers

#endif  // RANG_TERM_MODIFIERS_HPP_
