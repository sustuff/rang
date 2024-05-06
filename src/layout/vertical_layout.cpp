#include "layout/vertical_layout.hpp"

VerticalLayout::VerticalLayout(const term::window_dimensions& dims,
                               Layout* left,
                               Layout* right,
                               float ratio,
                               QObject* parent)
    : Layout(parent), m_left(left), m_right(right), m_ratio(ratio) {
  setDimensions(dims);
}

void VerticalLayout::recalculate() {
  int left_size_x = static_cast<int>(static_cast<float>(dimensions_.size_x) * m_ratio);
  m_left->setDimensions(
      {dimensions_.offset_x, dimensions_.offset_y, left_size_x, dimensions_.size_y});
  m_right->setDimensions({dimensions_.offset_x + left_size_x, dimensions_.offset_y,
                          dimensions_.size_x - left_size_x, dimensions_.size_y});
}

#include "layout/moc_vertical_layout.cpp"
