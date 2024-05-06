#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <QObject>

#include "term/window.hpp"

class Layout : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

    void setDimensions(const term::window_dimensions& dims);

  public slots:
    /// Recalculate children window/layout sizes.
    virtual void recalculate() = 0;

  protected:
    term::window_dimensions dimensions_;
};

#endif  // LAYOUT_HPP
