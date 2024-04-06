#include "ipc/connection_to_client_handler.hpp"

#include <QVariant>

#include "ipc/messages/messages.hpp"
#include "main_task.hpp"

void ConnectionToClientHandler::handleIncomingMessage(QByteArray data) {
  // TODO убедиться, что поток тут не заблокируется, если нам пришел только кусок команды

  QDataStream stream(data);

  QVariant message;
  stream >> message;

  if (auto msg = get_if<SetCurrentDirMessage>(&message); msg != nullptr) {
    MainTask::instance()->appState()->currentDir.setPath(msg->newPath.toStdString());
    qInfo() << "handled SetCurrentDir message";
  } else {
    qInfo() << "unknown incoming message";
  }
}

#include "ipc/moc_connection_to_client_handler.cpp"
