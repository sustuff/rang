#include "layout/horizontal_layout.hpp"

HorizontalLayout::HorizontalLayout(const term::window_dimensions& dims,
                               Layout* upper,
                               Layout* lower,
                               float ratio,
                               QObject* parent)
    : Layout(parent), m_upper(upper), m_lower(lower), m_ratio(ratio) {
  setDimensions(dims);
}

void HorizontalLayout::recalculate() {
  int upper_size_y = static_cast<int>(static_cast<float>(dimensions_.size_y) * m_ratio);
  m_upper->setDimensions(
      {dimensions_.offset_x, dimensions_.offset_y, dimensions_.size_x, upper_size_y});
  m_lower->setDimensions({dimensions_.offset_x, dimensions_.offset_y + upper_size_y,
                          dimensions_.size_x, dimensions_.size_y - upper_size_y});
}

#include "layout/moc_horizontal_layout.cpp"
