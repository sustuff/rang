#ifndef RANG_INCLUDE_COMMANDS_COMMAND_HPP_
#define RANG_INCLUDE_COMMANDS_COMMAND_HPP_

#include "app_state.hpp"

class Command {
  public:
    explicit Command(AppState* state);

    virtual void execute() = 0;

  protected:
    AppState* m_state{};
};

#endif  // RANG_INCLUDE_COMMANDS_COMMAND_HPP_
