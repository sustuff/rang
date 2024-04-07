#include "user_input.hpp"
#include <iostream>
#include "commands/set_current_dir_command.hpp"
#include "commands/set_preview_file_command.hpp"

UserInput::UserInput(AppState* appState, FileListBuffer* fileListBuffer)
    : QObject{appState}, m_appState{appState}, m_fileListBuffer{fileListBuffer} {
  QKeyCombination h{Qt::Key_H};
  QKeyCombination j{Qt::Key_J};
  QKeyCombination k{Qt::Key_K};
  QKeyCombination l{Qt::Key_L};
  m_parser.registerKeystroke({h}, [this]() { goToParentDir(); });
  m_parser.registerKeystroke({j}, [this]() { goDown(); });
  m_parser.registerKeystroke({k}, [this]() { goUp(); });
}

const QString& UserInput::currentCommand() {
  return m_currentCommand;
}

void UserInput::handleChar() {
  char key = std::getchar();
  if (m_currentCommand.isEmpty() && key != ':') {
    m_parser.nextKeyCombination(simpleKeyCombination(key));
  } else if (key == '\n') {
    handleCommand();
  } else if (key == 0x1b) {
    // Esc
    m_currentCommand.clear();
    emit currentCommandChanged();
  } else {
    m_currentCommand.append(key);
    emit currentCommandChanged();
  }
}

void UserInput::handleCommand() {
  if (m_currentCommand.startsWith(":q")) {
    emit m_appState->finished();
  } else if (m_currentCommand.startsWith(":o")) {
    SetCurrentDirCommand(m_appState, m_currentCommand.split(" ")[1].toStdString()).execute();
  } else if (m_currentCommand.startsWith(":p")) {
    SetPreviewFileCommand(m_appState, m_currentCommand.split(" ")[1].toStdString()).execute();
  }
  m_currentCommand.clear();
  emit currentCommandChanged();
}

void UserInput::goToParentDir() {
  m_appState->currentDir.setPath(
      std::filesystem::canonical(m_appState->currentDir.path()).parent_path());
}

void UserInput::goDown() {
}

void UserInput::goUp() {
}

QKeyCombination UserInput::simpleKeyCombination(char key) {
  if ('a' <= key && key <= 'z') {
    return static_cast<Qt::Key>(std::toupper(key));
  }
  return Qt::Key_unknown;
}

#include "moc_user_input.cpp"
