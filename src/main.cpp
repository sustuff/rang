#include <QtCore>

#include "main_task.hpp"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  auto* task = new MainTask(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(run()));

  return QCoreApplication::exec();
}
