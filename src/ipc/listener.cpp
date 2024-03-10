#include "listener.hpp"
#include "connection_handler.hpp"

Listener::Listener(QObject* parent) : QObject(parent) {
  QLocalServer::removeServer("rang-m_server");
  if (!m_server->listen("rang-m_server")) {
    qCritical() << "couldn't serve";
  }
  connect(m_server, &QLocalServer::newConnection, this, &Listener::handleNewConnection);
}

void Listener::handleNewConnection() {
  QLocalSocket* socket = m_server->nextPendingConnection();
  new ConnectionHandler(socket, this);
}

Listener::~Listener() {
  m_server->close();
}

#include "moc_listener.cpp"
