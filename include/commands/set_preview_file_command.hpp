#ifndef RANG_INCLUDE_COMMANDS_SET_PREVIEW_FILE_COMMAND_HPP_
#define RANG_INCLUDE_COMMANDS_SET_PREVIEW_FILE_COMMAND_HPP_

#include "commands/command.hpp"

class SetPreviewFileCommand : public Command {
  public:
    SetPreviewFileCommand(AppState* state, std::filesystem::path newPath);

    void execute() override;

  protected:
    std::filesystem::path m_newPath;
};

#endif  // RANG_INCLUDE_COMMANDS_SET_PREVIEW_FILE_COMMAND_HPP_
