#include "layout/layout.hpp"

void Layout::setDimensions(const term::window_dimensions& dims) {
  dimensions_ = dims;
  recalculate();
}


#include "layout/moc_layout.cpp"
