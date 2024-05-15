#include "term/manip.hpp"
#include <format>

namespace term::manip {
terminal_stream& operator<<(terminal_stream& ts, const alternate_buffer& m) {
  return ts << (raw::esc + "[?1049" + raw::hl(m.enable));
}

terminal_stream& operator<<(terminal_stream& ts, const cursor& m) {
  return ts << (raw::esc + "[?25" + raw::hl(m.show));
}

terminal_stream& operator<<(terminal_stream& ts, const clear&) {
  return ts << (raw::esc + "[2J");
}

window_stream& operator<<(window_stream& ws, const clear&) {
  // ouch
  std::string empty(ws.dimensions.size_x, ' ');
  for (int y = 1; y <= ws.dimensions.size_y; ++y) {
    ws << move{1, y} << empty;
  }
  return ws;
}

terminal_stream& operator<<(terminal_stream& ts, const move& m) {
  return ts << (raw::esc + std::format("[{};{}H", m.y, m.x));
}

window_stream& operator<<(window_stream& ws, const move& m) {
  return ws << (raw::esc +
                std::format("[{};{}H", ws.dimensions.offset_y + m.y, ws.dimensions.offset_x + m.x));
}

std::string true_color(bool background, uint8_t r, uint8_t g, uint8_t b) {
  return raw::esc + std::format("[{};2;{};{};{}m", (background ? 48 : 38), r, g, b);
}
}  // namespace term::manip
