#include "listener.hpp"
#include "connection_to_client_handler.hpp"

Listener::Listener(QObject* parent) : QObject(parent) {
  QLocalServer::removeServer("rang-server");  // TODO: unique server name and authentication
  if (!m_server->listen("rang-server")) {
    qCritical() << "couldn't serve";
  }
  connect(m_server, &QLocalServer::newConnection, this, &Listener::handleNewConnection);
}

void Listener::handleNewConnection() {
  QLocalSocket* socket = m_server->nextPendingConnection();
  new ConnectionToClientHandler(socket, this);
}

Listener::~Listener() {
  m_server->close();
}

#include "moc_listener.cpp"
