#ifndef RANG_SRC_WINDOW_RENDERER_HPP_
#define RANG_SRC_WINDOW_RENDERER_HPP_

#include <QObject>

class Renderer : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;
};

#endif  // RANG_SRC_WINDOW_RENDERER_HPP_
