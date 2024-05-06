#ifndef VERTICAL_LAYOUT_HPP
#define VERTICAL_LAYOUT_HPP

#include "layout/layout.hpp"

class VerticalLayout : public Layout {
    Q_OBJECT
  public:
    explicit VerticalLayout(const term::window_dimensions& dims,
                            Layout* left,
                            Layout* right,
                            float ratio = 0.5,
                            QObject* parent = nullptr);

    void recalculate() final;

  protected:
    float m_ratio;
    Layout* m_left;
    Layout* m_right;
};

#endif  // VERTICAL_LAYOUT_HPP
