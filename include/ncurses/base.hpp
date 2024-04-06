#ifndef RANG_BASE_HPP_
#define RANG_BASE_HPP_

#include "window.hpp"

namespace ncurses {
class base_window : public window {
  public:
    base_window();

    ~base_window();
};
}  // namespace ncurses

#endif  // RANG_BASE_HPP_
