#include "main_task.hpp"
#include "buffer/text_file_preview_buffer.hpp"
#include "renderer/command_renderer.hpp"
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
  auto* filePreviewBuffer = new TextFilePreviewBuffer(this);

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
  connect(&m_appState->previewPath, &PathRegister::changed, filePreviewBuffer,
          &TextFilePreviewBuffer::setPath);
  connect(watcher, &QFileSystemWatcher::directoryChanged, fileListBuffer, &FileListBuffer::update);

  m_appState->currentDir.setPath(".");
  m_appState->previewPath.setPath("");

  term = std::make_unique<term::terminal>();
  auto fileListWindow = std::make_shared<term::window>(
      *term, term::window_dimensions{0, 0, term->width() / 2, term->height() - 1});
  auto filePreviewWindow = std::make_shared<term::window>(
      *term, term::window_dimensions{term->width() / 2, 4, term->width() - term->width() / 2,
                                     term->height() - 5});
  auto fileInfoWindow = std::make_shared<term::window>(
      *term, term::window_dimensions{term->width() / 2, 0, term->width() - term->width() / 2, 4});
  auto commandWindow = std::make_shared<term::window>(
      *term, term::window_dimensions{0, term->height() - 2, term->width(), 1});
  auto* fileListRenderer = new TextRenderer(fileListBuffer, fileListWindow);
  auto* filePreviewRenderer = new TextRenderer(filePreviewBuffer, filePreviewWindow);
  auto* fileInfoRenderer = new TextRenderer(fileInfoBuffer, fileInfoWindow);
  auto* commandRenderer = new CommandRenderer(commandWindow);

  auto* userInput = new UserInput(m_appState, fileListBuffer);
  connect(userInput, &UserInput::hasReset, commandRenderer, &CommandRenderer::reset);
  connect(userInput, &UserInput::gotChar, commandRenderer, &CommandRenderer::putChar);
  connect(userInput, &UserInput::gotPopBack, commandRenderer, &CommandRenderer::popBack);

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, userInput, &UserInput::handleChar);

  connect(m_appState, &AppState::finished, [this]() { emit finished(); });

  fileListBuffer->update();
  fileInfoBuffer->update();
  filePreviewBuffer->update();
}

AppState* MainTask::appState() const {
  return m_appState;
}

QString MainTask::getRemoteControlToken() const {
  return m_remoteControlToken;
}

#include "moc_main_task.cpp"
