#include "main_task.hpp"

#include "app_info.hpp"
#include "app_state.hpp"

MainTask::MainTask(QObject* parent) : QObject(parent) {
}

void MainTask::run() {
  qInfo("running %s (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::build_date.toString()));

  auto state = QSharedPointer<AppState>::create();
  state->current_dir.file = QFileInfo("/");

  emit finished();
}

#include "moc_main_task.cpp"
