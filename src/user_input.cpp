#include "user_input.hpp"
#include <iostream>
#include "commands/set_current_dir_command.hpp"
#include "commands/set_preview_file_command.hpp"
#include "unix_signal.hpp"

UserInput::UserInput(AppState* appState, FileListBuffer* fileListBuffer)
    : QObject{appState}, m_appState{appState}, m_fileListBuffer{fileListBuffer} {
  auto* sigint = new UnixSignal(SIGINT, this);
  connect(sigint, &UnixSignal::received, [this] { emit m_appState->finished(); });

  QKeyCombination h{Qt::Key_H};
  QKeyCombination j{Qt::Key_J};
  QKeyCombination k{Qt::Key_K};
  QKeyCombination l{Qt::Key_L};
  QKeyCombination enter{Qt::Key_Return};
  m_parser.registerKeystroke({h}, [this] { goToParentDir(); });
  m_parser.registerKeystroke({j}, [this] { emit goDown(); });
  m_parser.registerKeystroke({k}, [this] { emit goUp(); });
  m_parser.registerKeystroke({l}, [this] { emit goToChildDir(); });
  m_parser.registerKeystroke({enter}, [this] { emit goToChildDir(); });
}

const std::string& UserInput::currentCommand() {
  return m_currentCommand;
}

void UserInput::handleChar() {
  char key = std::getchar();
  if (m_currentCommand.empty() && key != ':') {
    m_parser.nextKeyCombination(simpleKeyCombination(key));
  } else if (key == '\n') {
    handleCommand();
  } else if (key == 0x7F) {
    m_currentCommand.pop_back();
    emit gotPopBack();
  } else if (key == 0x1b) {
    // Esc
    m_currentCommand.clear();
    emit hasReset();
  } else {
    m_currentCommand.push_back(key);
    emit gotChar(key);
  }
}

void UserInput::handleCommand() {
  if (m_currentCommand.starts_with(":q")) {
    emit m_appState->finished();
  } else if (m_currentCommand.starts_with(":o")) {
    SetCurrentDirCommand(m_appState,
                         QString::fromStdString(m_currentCommand).split(" ")[1].toStdString())
        .execute();
  } else if (m_currentCommand.starts_with(":p")) {
    SetPreviewFileCommand(m_appState,
                          QString::fromStdString(m_currentCommand).split(" ")[1].toStdString())
        .execute();
  }
  m_currentCommand.clear();
  emit hasReset();
}

void UserInput::goToParentDir() {
  m_appState->currentDir.setPath(canonical(m_appState->currentDir.path()).parent_path());
}

QKeyCombination UserInput::simpleKeyCombination(char key) {
  if ('a' <= key && key <= 'z') {
    return static_cast<Qt::Key>(std::toupper(key));
  }
  if (key == '\n') {
    return Qt::Key_Return;
  }
  return Qt::Key_unknown;
}

#include "moc_user_input.cpp"
