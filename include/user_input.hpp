#ifndef RANG_SRC_USER_INPUT_HPP_
#define RANG_SRC_USER_INPUT_HPP_

#include "app_state.hpp"
#include "buffer/file_list_buffer.hpp"
#include "keystroke_parser.hpp"

class UserInput : public QObject {
    Q_OBJECT
  public:
    UserInput(AppState* appState, FileListBuffer* fileListBuffer);

    const std::string& currentCommand();

  signals:
    void gotChar(char);
    void hasReset();
    void gotPopBack();
    void goDown();
    void goUp();
    void goToChildDir();

  public slots:
    void handleChar();

  private:
    AppState* m_appState;
    FileListBuffer* m_fileListBuffer;
    KeystrokeParser m_parser;
    std::string m_currentCommand;

    void handleCommand();
    void goToParentDir();

    static QKeyCombination simpleKeyCombination(char key);
};

#endif  // RANG_SRC_USER_INPUT_HPP_
