#ifndef RANG_SRC_BUFFER_BUFFER_HPP_
#define RANG_SRC_BUFFER_BUFFER_HPP_

#include <QObject>

#include "text/line.hpp"

/// Buffers provide some information which can later go through Renderer.
class Buffer : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

    virtual QVector<Line> getLines() = 0;

  public slots:
    virtual void update() = 0;

  signals:
    void contentChanged();
};

#endif  // RANG_SRC_BUFFER_BUFFER_HPP_
