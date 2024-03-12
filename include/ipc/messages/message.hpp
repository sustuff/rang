#ifndef RANG_SRC_IPC_MESSAGES_MESSAGE_HPP_
#define RANG_SRC_IPC_MESSAGES_MESSAGE_HPP_

#include "set_current_dir_message.hpp"

/// Universal Message class which can represent any message type.
/// Used for message transportation over local sockets.
struct Message {
    enum class Type {
      Empty,
      SetCurrentDir,
    };
    Type type;
    std::variant<std::monostate, SetCurrentDirMessage> message;
};

#endif  // RANG_SRC_IPC_MESSAGES_MESSAGE_HPP_
