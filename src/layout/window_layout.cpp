#include "layout/window_layout.hpp"

WindowLayout::WindowLayout(const term::window_dimensions& dims, Renderer* renderer, QObject* parent)
    : Layout(parent), renderer(renderer) {
  setDimensions(dims);
}

void WindowLayout::recalculate() {
  renderer->changeDimensions(dimensions_);
  renderer->refresh();
}

#include "layout/moc_window_layout.cpp"
