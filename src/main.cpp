#include <QtCore>

#include "main_task.hpp"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  auto* task = new MainTask(&a);
  QObject::connect(task, &MainTask::finished, &a, &QCoreApplication::quit);
  QTimer::singleShot(0, task, &MainTask::run);

  return QCoreApplication::exec();
}
