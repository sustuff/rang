#ifndef RANG_SRC_CLIENT_TASK_HPP_
#define RANG_SRC_CLIENT_TASK_HPP_

#include <QVariant>

/// Entry point in client mode.
class ClientTask : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

  public slots:
    void run(const QString& token, const QVariant& message);

  signals:
    void finished();
};

#endif  // RANG_SRC_CLIENT_TASK_HPP_
