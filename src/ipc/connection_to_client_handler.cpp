#include "ipc/connection_to_client_handler.hpp"

#include <QVariant>

#include "compatibility.hpp"
#include "ipc/messages/authentication_message.hpp"
#include "ipc/messages/messages.hpp"
#include "main_task.hpp"

void ConnectionToClientHandlerThread::handleIncomingMessage(QVariant message) {
  MainTask* main_task = MainTask::instance();
  QMutexLocker lock(main_task->mutex());

  if (auto msg = get_if<AuthenticationMessage>(&message); msg != nullptr) {
    if (msg->token == main_task->getRemoteControlToken()) {
      authenticated_ = true;
    }
    return;
  }

  // Ignore other messages from non-authenticated clients.
  if (!authenticated_)
    return;

  if (auto msg = get_if<SetCurrentDirMessage>(&message); msg != nullptr) {
    MainTask::instance()->appState()->currentDir.setPath(msg->newPath.toStdString());
    qInfo() << "handled SetCurrentDir message";
  } else {
    qInfo() << "unknown incoming message";
  }
}

#include "ipc/moc_connection_to_client_handler.cpp"
