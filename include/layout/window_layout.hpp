#ifndef WINDOW_LAYOUT_HPP
#define WINDOW_LAYOUT_HPP

#include "layout/layout.hpp"
#include "renderer/renderer.hpp"

/// Holds single window.
class WindowLayout : public Layout {
    Q_OBJECT
  public:
    explicit WindowLayout(const term::window_dimensions& dims,
                          Renderer* renderer,
                          QObject* parent = nullptr);

    void recalculate() final;

  protected:
    Renderer* renderer;
};

#endif  // WINDOW_LAYOUT_HPP
