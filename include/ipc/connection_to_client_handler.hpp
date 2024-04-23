#ifndef RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_
#define RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_

#include "connection_handler.hpp"

/// Created by Listener class.
class ConnectionToClientHandlerThread : public ConnectionHandlerThread {
    Q_OBJECT
  public:
    using ConnectionHandlerThread::ConnectionHandlerThread;

    void handleIncomingMessage(QVariant msg) override;

  private:
    bool authenticated_{};
};

#endif  // RANG_SRC_IPC_CONNECTION_TO_CLIENT_HANDLER_HPP_
