#ifndef RANG_SRC_IPC_LISTENER_HPP_
#define RANG_SRC_IPC_LISTENER_HPP_

#include <QtCore>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

/// Listens on a local socket; connected clients can execute arbitrary commands.
/// Used for interaction with app in client mode. Security is achieved by providing a unique
/// access token through environment variable to a child shell process.
class Listener : public QObject {
    Q_OBJECT
  public:
    explicit Listener(QObject* parent = nullptr);
    ~Listener() override;

  private slots:
    void handleNewConnection();

  private:
    QLocalServer* m_server{new QLocalServer()};
};

#endif  // RANG_SRC_IPC_LISTENER_HPP_
