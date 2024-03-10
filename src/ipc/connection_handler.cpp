#include "connection_handler.hpp"

ConnectionHandler::ConnectionHandler(QLocalSocket* socketIn, QObject* parent)
    : QObject(parent), m_socket(socketIn) {
  qInfo() << "connection handler called";

  m_readNotifier = new QSocketNotifier(socketIn->socketDescriptor(), QSocketNotifier::Read, this);
  //  auto* writeNotifier =
  //      new QSocketNotifier(socketIn->socketDescriptor(), QSocketNotifier::Write, this);

  connect(m_socket, &QLocalSocket::stateChanged, this, &ConnectionHandler::onSocketStateChanged);
  connect(m_readNotifier, &QSocketNotifier::activated, this, &ConnectionHandler::dataAvailable);
}

void ConnectionHandler::onSocketStateChanged(QLocalSocket::LocalSocketState state) {
  if (state == QLocalSocket::LocalSocketState::ClosingState) {
    m_readNotifier->setSocket(-1);
  }
}

void ConnectionHandler::dataAvailable() {
  qInfo() << "data available";
  auto msg = m_socket->readAll();
  emit incomingMessage(std::move(msg));
}

#include "moc_connection_handler.cpp"
