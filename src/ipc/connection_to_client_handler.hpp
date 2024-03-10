#ifndef RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_
#define RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_

#include "connection_handler.hpp"

class ConnectionToClientHandler : public ConnectionHandler {
    Q_OBJECT
  public:
    using ConnectionHandler::ConnectionHandler;

    void handleIncomingMessage(QByteArray data) override;
};

#endif  // RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_
