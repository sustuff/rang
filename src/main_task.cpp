#include "main_task.hpp"
#include "buffer/text_file_preview_buffer.hpp"
#include "renderer/text_renderer.hpp"
#include "user_input.hpp"

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

  auto* userInput = new UserInput(m_appState, fileListBuffer);

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
  m_appState->previewPath.setPath("");

  term = std::make_unique<term::terminal>();

  auto* fileListRenderer = new TextRenderer(fileListBuffer);
  auto* fileInfoRenderer = new TextRenderer(fileInfoBuffer);
  auto* previewRenderer = new TextRenderer(previewBuffer);

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, userInput, &UserInput::handleChar);

  connect(m_appState, &AppState::finished, [this]() { emit finished(); });

  fileListBuffer->update();
  fileInfoBuffer->update();
  previewBuffer->update();
}

AppState* MainTask::appState() const {
  return m_appState;
}

QString MainTask::getRemoteControlToken() const {
  return m_remoteControlToken;
}

#include "moc_main_task.cpp"
