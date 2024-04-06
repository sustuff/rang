#include "ipc/listener.hpp"
#include "ipc/connection_to_client_handler.hpp"

Listener::Listener(QObject* parent) : QObject(parent) {
  QLocalServer::removeServer("rang-server");  // TODO: unique server name
  if (!m_server->listen("rang-server")) {
    qCritical() << "couldn't serve";
  }
  connect(m_server, &QLocalServer::newConnection, this, &Listener::handleNewConnection);
}

void Listener::handleNewConnection() {
  QLocalSocket* socket = m_server->nextPendingConnection();
  auto thread = new ConnectionToClientHandlerThread(socket, this);
  connect(thread, &ConnectionToClientHandlerThread::finished, thread,
          &ConnectionToClientHandlerThread::deleteLater);
  thread->start();
}

Listener::~Listener() {
  m_server->close();
}

#include "ipc/moc_listener.cpp"
