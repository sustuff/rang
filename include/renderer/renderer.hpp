#ifndef RANG_SRC_WINDOW_RENDERER_HPP_
#define RANG_SRC_WINDOW_RENDERER_HPP_

#include <QObject>

#include "term/window.hpp"

class Renderer : public QObject {
    Q_OBJECT
  public:
    explicit Renderer(std::unique_ptr<term::window> window, QObject* parent = nullptr);

    virtual void refresh() = 0;
    void changeDimensions(const term::window_dimensions& dims);

  protected:
    std::unique_ptr<term::window> m_window;
};

#endif  // RANG_SRC_WINDOW_RENDERER_HPP_
