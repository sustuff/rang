#include "ipc/connection_handler.hpp"

ConnectionHandlerThread::ConnectionHandlerThread(QLocalSocket* socketIn, QObject* parent)
    : QThread(parent), m_socket(socketIn) {
  qInfo() << "connection handler called";

  connect(m_socket, &QLocalSocket::stateChanged, this,
          &ConnectionHandlerThread::onSocketStateChanged);
}

void ConnectionHandlerThread::onSocketStateChanged(QLocalSocket::LocalSocketState state) {
  if (state == QLocalSocket::LocalSocketState::ClosingState) {
    //    m_wrappingUp = true;
  }
}

void ConnectionHandlerThread::run() {
  QDataStream stream(m_socket);
  while (!m_wrappingUp) {
    QVariant msg;
    stream >> msg;
    if (!msg.isValid()) {
      break;
    }
    qInfo() << "Got message" << msg;
    handleIncomingMessage(msg);
  }
}

#include "ipc/moc_connection_handler.cpp"
