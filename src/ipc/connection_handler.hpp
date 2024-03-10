#ifndef RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
#define RANG_SRC_IPC_CONNECTION_HANDLER_HPP_

#include <QtCore>

class ConnectionHandler : public QObject {
    Q_OBJECT
  public:
    explicit ConnectionHandler(QLocalSocket* socketIn, QObject* parent = nullptr);

  private slots:
    void dataAvailable();
    void onSocketStateChanged(QLocalSocket::LocalSocketState state);

  signals:
    void incomingMessage(QByteArray data);

  private:
    QLocalSocket* m_socket;
    QSocketNotifier* m_readNotifier{};
};

#endif  // RANG_SRC_IPC_CONNECTION_HANDLER_HPP_
