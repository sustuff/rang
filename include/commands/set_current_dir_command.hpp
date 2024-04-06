#ifndef RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_
#define RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_

#include "commands/command.hpp"

class SetCurrentDirCommand : public Command {
  public:
    using Command::Command;

    void execute(const std::filesystem::path& newPath);
};

#endif  // RANG_INCLUDE_COMMANDS_SET_CURRENT_DIR_COMMAND_HPP_
