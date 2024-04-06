#include "main_task.hpp"
#include <iostream>
#include "buffer/text_file_preview_buffer.hpp"

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
  qInfo("running %s v%s (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::versionString), qUtf8Printable(AppInfo::buildDate.toString()));

  m_appState = new AppState(this);
  m_listener = new Listener(this);

  auto* fileListBuffer = new FileListBuffer(this);
  auto* fileInfoBuffer = new FileInfoBuffer(this);
  auto* previewBuffer = new TextFilePreviewBuffer(this);

  connect(&m_appState->currentDir, &PathRegister::changed, fileListBuffer,
          &FileListBuffer::setPath);
  auto* watcher = new QFileSystemWatcher(this);

  connect(&m_appState->currentDir, &PathRegister::changed,
          [watcher](const std::filesystem::path& newPath) {
            auto path = QString::fromStdString(newPath);
            watcher->removePath(path);
            watcher->addPath(path);
          });
  connect(&m_appState->previewPath, &PathRegister::changed, fileInfoBuffer,
          &FileInfoBuffer::setPath);
  connect(&m_appState->previewPath, &PathRegister::changed, previewBuffer,
          &TextFilePreviewBuffer::setPath);
  connect(watcher, &QFileSystemWatcher::directoryChanged, fileListBuffer, &FileListBuffer::update);

  m_appState->currentDir.setPath(".");
  m_appState->previewPath.setPath("./main.cpp");

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, [=, this]() {
    auto draw = [&]() {
      fileListBuffer->update();
      fileInfoBuffer->update();
      previewBuffer->update();

      auto list1 = fileListBuffer->getLines();
      auto list2 = fileInfoBuffer->getLines();
      list2.append("===========================================");
      list2 += previewBuffer->getLines();
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

    std::string str_;
    std::getline(std::cin, str_);
    QString str = QString::fromStdString(str_);
    if (str == ":q") {
      emit finished();
    } else if (str.startsWith(":o")) {
      m_appState->currentDir.setPath(str.split(" ")[1].toStdString());
    } else if (str.startsWith(":p")) {
      m_appState->previewPath.setPath(str.split(" ")[1].toStdString());
    }
    draw();
  });
}

LockedAppState MainTask::appState() const {
  return {m_appState, &m_mutex};
}


QString MainTask::getRemoteControlToken() const {
  return m_remoteControlToken;
}

#include "moc_main_task.cpp"
