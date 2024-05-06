#include "main_task.hpp"
#include "app_info.hpp"
#include "buffer/file_info_buffer.hpp"
#include "buffer/text_file_preview_buffer.hpp"
#include "layout/horizontal_layout.hpp"
#include "layout/vertical_layout.hpp"
#include "layout/window_layout.hpp"
#include "renderer/command_renderer.hpp"
#include "renderer/text_renderer.hpp"
#include "user_input.hpp"

MainTask* MainTask::instance() {
  return self;
}

MainTask::MainTask(QObject* parent) : QObject(parent) {
  if (self) {
    throw QException();  // only one instance is allowed
  }
  self = this;
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

  auto fileListWindow = std::make_unique<term::window>(*term, term::window_dimensions{});
  auto filePreviewWindow = std::make_unique<term::window>(*term, term::window_dimensions{});
  auto fileInfoWindow = std::make_unique<term::window>(*term, term::window_dimensions{});
  auto commandWindow = std::make_unique<term::window>(
      *term, term::window_dimensions{0, term->height() - 2, term->width(), 1});

  auto* fileListRenderer = new TextRenderer(fileListBuffer, std::move(fileListWindow));
  auto* filePreviewRenderer = new TextRenderer(filePreviewBuffer, std::move(filePreviewWindow));
  auto* fileInfoRenderer = new TextRenderer(fileInfoBuffer, std::move(fileInfoWindow));
  auto* commandRenderer = new CommandRenderer(std::move(commandWindow));

  auto* fileListLayout = new WindowLayout(term::window_dimensions{}, fileListRenderer);
  auto* filePreviewLayout = new WindowLayout(term::window_dimensions{}, filePreviewRenderer);
  auto* fileInfoLayout = new WindowLayout(term::window_dimensions{}, fileInfoRenderer);
  auto* rootLayout = new VerticalLayout(
      term::window_dimensions{0, 0, term->width(), term->height() - 1}, fileListLayout,
      new HorizontalLayout(term::window_dimensions{}, fileInfoLayout, filePreviewLayout, 0.1));
  rootLayout->recalculate();

  connect(fileListBuffer, &FileListBuffer::currentFileChanged, m_appState,
          &AppState::setPreviewPath);

  auto* userInput = new UserInput(m_appState, fileListBuffer);
  connect(userInput, &UserInput::hasReset, commandRenderer, &CommandRenderer::reset);
  connect(userInput, &UserInput::gotChar, commandRenderer, &CommandRenderer::putChar);
  connect(userInput, &UserInput::gotPopBack, commandRenderer, &CommandRenderer::popBack);
  connect(userInput, &UserInput::goDown, fileListBuffer, &FileListBuffer::goDown);
  connect(userInput, &UserInput::goUp, fileListBuffer, &FileListBuffer::goUp);
  connect(userInput, &UserInput::goToChildDir, [this, fileListBuffer = fileListBuffer]() {
    if (fileListBuffer) {
      auto currentFile = fileListBuffer->getCurrentFile();
      namespace fs = std::filesystem;
      if (currentFile.has_value() &&
          fs::status(currentFile.value()).type() == fs::file_type::directory) {
        m_appState->currentDir.setPath(std::move(currentFile.value()));
      }
    }
  });

  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, userInput, &UserInput::handleChar);

  connect(m_appState, &AppState::finished, [this] { emit finished(); });

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
