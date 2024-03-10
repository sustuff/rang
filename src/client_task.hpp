#ifndef RANG_SRC_CLIENT_TASK_HPP_
#define RANG_SRC_CLIENT_TASK_HPP_

#include <QtCore>

class ClientTask : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

  public slots:
    void run(const QString& newPath);

  signals:
    void finished();
};

#endif  // RANG_SRC_CLIENT_TASK_HPP_
