#ifndef RANG_SRC_MAIN_TASK_HPP_
#define RANG_SRC_MAIN_TASK_HPP_

#include <QtCore>

class MainTask : public QObject {
    Q_OBJECT
  public:
    explicit MainTask(QObject* parent = nullptr);

  public slots:
    void run();

  signals:
    void finished();
};

#endif  // RANG_SRC_MAIN_TASK_HPP_
