#include "ipc/connection_to_client_handler.hpp"
#include "main_task.hpp"

void ConnectionToClientHandler::handleIncomingMessage(QByteArray data) {
  // TODO убедиться, что поток тут не заблокируется, если нам пришел только кусок команды
  // TODO считывать Message и обрабатывать разные типы сообщений
  QDataStream stream(data);
  QString newPath;
  stream >> newPath;
  MainTask::instance()->appState()->currentDir.setPath(newPath.toStdString());
  qInfo() << "handled incoming message" << newPath;
}

#include "ipc/moc_connection_to_client_handler.cpp"
