#ifndef RANG_SRC_USER_INPUT_HPP_
#define RANG_SRC_USER_INPUT_HPP_

#include "app_state.hpp"
#include "buffer/file_list_buffer.hpp"
#include "keystroke_parser.hpp"

class UserInput : public QObject {
    Q_OBJECT
  public:
    UserInput(AppState* appState, FileListBuffer* fileListBuffer);

  public slots:
    void handleChar();

  private:
    AppState* appState;
    FileListBuffer* fileListBuffer;
    KeystrokeParser parser;
    QString currentCommand;

    void handleCommand();
    void goToParentDir();
    void goDown();
    void goUp();

    static QKeyCombination simpleKeyCombination(char key);
};

#endif  // RANG_SRC_USER_INPUT_HPP_
