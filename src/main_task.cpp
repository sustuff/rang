#include "main_task.hpp"

MainTask* MainTask::instance() {
  return MainTask::self;
}

MainTask::MainTask(QObject* parent) : QObject(parent) {
  if (MainTask::self) {
    throw QException();  // only one instance is allowed
  }
  MainTask::self = this;
}

void MainTask::run() {
  qInfo("running %s (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::buildDate.toString()));

  appState = new AppState(this);
  listener = new Listener(this);

  auto* file_list_buffer = new FileListBuffer(this);
  auto* preview_buffer = new FileInfoBuffer(this);

  connect(&appState->current_dir, &PathRegister::changed, file_list_buffer,
          [=](const QFileInfo& file) { file_list_buffer->setPath(file.filesystemFilePath()); });
  connect(&appState->preview_path, &PathRegister::changed, preview_buffer,
          [=](const QFileInfo& file) { preview_buffer->setPath(file.filesystemFilePath()); });

  auto draw = [&]() {
    file_list_buffer->update();
    preview_buffer->update();

    auto list1 = file_list_buffer->getLines();
    auto list2 = preview_buffer->getLines();
    QString result;
    qsizetype n = qMax(list1.size(), list2.size());
    for (qsizetype i = 0; i < n; ++i) {
      result +=
          (list1.value(i, "").leftJustified(80) + " | " + list2.value(i, "").leftJustified(80)) +
          "\n";
    }
    qInfo(
        "======================================================== listing ???? "
        "========================================================\n%s",
        qUtf8Printable(result));
  };

  appState->current_dir.setPath(QFileInfo("../src"));
  appState->preview_path.setPath(QFileInfo("../src/main.cpp"));
  draw();

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, this, &MainTask::finished);
}

#include "moc_main_task.cpp"
