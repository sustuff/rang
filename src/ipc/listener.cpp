#include "listener.hpp"
#include "connection_handler.hpp"

Listener::Listener(QObject* parent) : QObject(parent) {
  QLocalServer::removeServer("rang-server");
  if (!server->listen("rang-server")) {
    qCritical() << "couldn't serve";
  }
  connect(server, &QLocalServer::newConnection, this, &Listener::handleNewConnection);
}

void Listener::handleNewConnection() {
  QLocalSocket* socket = server->nextPendingConnection();
  new ConnectionHandler(socket, this);
}

Listener::~Listener() {
  server->close();
}

#include "moc_listener.cpp"
