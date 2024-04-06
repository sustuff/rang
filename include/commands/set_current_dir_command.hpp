#ifndef RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_
#define RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_

#include "commands/command.hpp"

class SetCurrentDirCommand : public Command {
  public:
    SetCurrentDirCommand(AppState* state, std::filesystem::path newPath);

    void execute() override;

  protected:
    std::filesystem::path m_newPath;
};

#endif  // RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_
