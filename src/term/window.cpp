#include "term/window.hpp"

namespace term {
window_stream::window_stream(terminal_stream& term, const window_dimensions& dim)
    : raw(term), dimensions(dim) {
}

window_stream& window_stream::operator<<(std::ostream& (*func)(std::ostream&)) {
  raw << func;
  return *this;
}

window::window(terminal& term, const window_dimensions& dim)
    : dimensions(dim), stream(term.stream, dimensions) {
}

}  // namespace term
