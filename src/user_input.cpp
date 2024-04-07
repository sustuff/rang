#include "user_input.hpp"
#include <iostream>
#include "commands/set_current_dir_command.hpp"
#include "commands/set_preview_file_command.hpp"

UserInput::UserInput(AppState* appState, FileListBuffer* fileListBuffer)
    : QObject{appState}, appState{appState}, fileListBuffer{fileListBuffer} {
  QKeyCombination h{Qt::Key_H};
  QKeyCombination j{Qt::Key_J};
  QKeyCombination k{Qt::Key_K};
  QKeyCombination l{Qt::Key_L};
  parser.registerKeystroke({h}, [this]() { goToParentDir(); });
  parser.registerKeystroke({j}, [this]() { goDown(); });
  parser.registerKeystroke({k}, [this]() { goUp(); });
}

void UserInput::handleChar() {
  char key = std::getchar();
  if (currentCommand.isEmpty() && key != ':') {
    parser.nextKeyCombination(simpleKeyCombination(key));
  } else if (key == '\n') {
    handleCommand();
  } else if (key == 0x1b) {
    // Esc
    currentCommand.clear();
  } else {
    currentCommand.append(key);
  }
}

void UserInput::handleCommand() {
  if (currentCommand.startsWith(":q")) {
    emit appState->finished();
  } else if (currentCommand.startsWith(":o")) {
    SetCurrentDirCommand(appState, currentCommand.split(" ")[1].toStdString()).execute();
  } else if (currentCommand.startsWith(":p")) {
    SetPreviewFileCommand(appState, currentCommand.split(" ")[1].toStdString()).execute();
  }
  currentCommand.clear();
}

void UserInput::goToParentDir() {
  appState->currentDir.setPath(
      std::filesystem::canonical(appState->currentDir.path()).parent_path());
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
