#ifndef RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
#define RANG_SRC_IPC_CONNECTION_HANDLER_HPP_

#include <QtCore>

/// Basic class for both client-to-server and server-to-client communications.
class ConnectionHandler : public QObject {
    Q_OBJECT
  public:
    explicit ConnectionHandler(QLocalSocket* socketIn, QObject* parent = nullptr);

  private slots:
    void dataAvailable();
    void onSocketStateChanged(QLocalSocket::LocalSocketState state);

  protected:
    virtual void handleIncomingMessage(QByteArray data) = 0;

  private:
    QLocalSocket* m_socket;
    QSocketNotifier* m_readNotifier{};
};

#endif  // RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
