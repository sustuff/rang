#ifndef RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
#define RANG_SRC_IPC_CONNECTION_HANDLER_HPP_

#include <QtCore>

/// Basic class for both client-to-server and server-to-client communications.
class ConnectionHandlerThread : public QThread {
    Q_OBJECT
  public:
    explicit ConnectionHandlerThread(QLocalSocket* socketIn, QObject* parent = nullptr);

    void run() override;
  private slots:
    void onSocketStateChanged(QLocalSocket::LocalSocketState state);

  protected:
    virtual void handleIncomingMessage(QVariant msg) = 0;

  private:
    QLocalSocket* m_socket;
    bool m_wrappingUp{};
};

#endif  // RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
