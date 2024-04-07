#include "main_task.hpp"
#include <iostream>
#include "buffer/text_file_preview_buffer.hpp"
#include "renderer/text_renderer.hpp"
#include "term/terminal.hpp"

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
  qInfo("running %s v%s (built %s)", qUtf8Printable(AppInfo::appName),
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
            current_path(newPath);
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
  m_appState->previewPath.setPath("");

  auto* term = new term::terminal;
  connect(this, &MainTask::destroyed, [=]() { delete term; });

  auto* fileListRenderer = new TextRenderer(fileListBuffer);
  auto* fileInfoRenderer = new TextRenderer(fileInfoBuffer);
  auto* previewRenderer = new TextRenderer(previewBuffer);

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, [=, this]() {
    auto draw = [&]() {
      fileListBuffer->update();
      fileInfoBuffer->update();
      previewBuffer->update();
    };

    std::string str_;
    std::getline(std::cin, str_);
    QString str = QString::fromStdString(str_);
    if (str == ":q") {
      emit finished();
    } else if (str.startsWith(":o") or str.startsWith("cd")) {
      m_appState->currentDir.setPath(str.split(" ")[1].toStdString());
      m_appState->previewPath.setPath("");
    } else if (str.startsWith(":p") or str.startsWith("p")) {
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
