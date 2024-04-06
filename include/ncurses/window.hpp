#ifndef RANG_WINDOW_HPP_
#define RANG_WINDOW_HPP_

#include <memory>
#include <vector>
#include "impl.hpp"

namespace ncurses {
class window {
  protected:
    impl::WINDOW* win_ptr = nullptr;
    int size_x = 0;
    int size_y = 0;
    int offset_x = 0;
    int offset_y = 0;

    std::weak_ptr<window> parent;
    std::vector<std::shared_ptr<window>> subwindows;

  public:
    window() = default;

    window(int size_x, int size_y, int offset_x, int offset_y, std::weak_ptr<window> parent);

    ~window();

    bool operator==(const window& other) const;

    int get_size_x() const;
    int get_size_y() const;
    int get_offset_x() const;
    int get_offset_y() const;

    // refresh current window
    void refresh() const;

    // move caret to given x, y
    void move_caret(int x, int y) const;

    // output line at a current position of a caret
    void output(const std::string& s) const;

    // move caret to position x, y and output line
    void move_caret_and_output(int x, int y, const std::string& s) const;

    // output full line at position y
    void output_line(int y, const std::string& s) const;

    // create a subwindow
    std::shared_ptr<window> subwindow(int size_x, int size_y, int offset_x, int offset_y);

    // enable F1-F12 keys
    int set_keypad(bool value) const;
};
}  // namespace ncurses

#endif  // RANG_WINDOW_HPP_
