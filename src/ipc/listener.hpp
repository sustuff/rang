#ifndef RANG_SRC_IPC_LISTENER_HPP_
#define RANG_SRC_IPC_LISTENER_HPP_

#include <QtCore>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

class Listener : public QObject {
    Q_OBJECT
  public:
    explicit Listener(QObject* parent = nullptr);
    ~Listener();

  private slots:
    void handleNewConnection();

  private:
    QLocalServer* server{new QLocalServer()};
};

#endif  // RANG_SRC_IPC_LISTENER_HPP_
