#ifndef HORIZONTAL_LAYOUT_HPP
#define HORIZONTAL_LAYOUT_HPP

#include "layout/layout.hpp"

class HorizontalLayout : public Layout {
    Q_OBJECT
  public:
    explicit HorizontalLayout(const term::window_dimensions& dims,
                            Layout* upper,
                            Layout* lower,
                            float ratio = 0.5,
                            QObject* parent = nullptr);

    void recalculate() final;

  protected:
    float m_ratio;
    Layout* m_upper;
    Layout* m_lower;
};

#endif  // HORIZONTAL_LAYOUT_HPP
