#include "main_task.hpp"
#include <iostream>

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

  m_appState = new AppState(this);
  m_listener = new Listener(this);

  auto* file_list_buffer = new FileListBuffer(this);
  auto* preview_buffer = new FileInfoBuffer(this);

  connect(&m_appState->currentDir, &PathRegister::changed, file_list_buffer,
          &FileListBuffer::setPath);
  connect(&m_appState->previewPath, &PathRegister::changed, preview_buffer,
          &FileInfoBuffer::setPath);
  auto* watcher = new QFileSystemWatcher(this);

  connect(&m_appState->currentDir, &PathRegister::changed,
          [watcher](const std::filesystem::path& newPath) {
            auto path = QString::fromStdString(newPath);
            watcher->removePath(path);
            watcher->addPath(path);
          });
  connect(&m_appState->previewPath, &PathRegister::changed, preview_buffer,
          &FileInfoBuffer::setPath);
  connect(watcher, &QFileSystemWatcher::directoryChanged, file_list_buffer,
          &FileListBuffer::update);

  m_appState->currentDir.setPath("../src");
  m_appState->previewPath.setPath("../src/main.cpp");

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, [=, this]() {
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

    std::string str;
    std::getline(std::cin, str);
    if (str == ":q") {
      emit finished();
    } else {
      draw();
    }
  });
}

AppState* MainTask::appState() const {
  return m_appState;
}

#include "moc_main_task.cpp"
