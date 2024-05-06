#include "ipc/connection_to_client_handler.hpp"

#include "commands/set_current_dir_command.hpp"
#include "commands/set_preview_file_command.hpp"
#include "ipc/messages/authentication_message.hpp"
#include "ipc/messages/messages.hpp"
#include "main_task.hpp"

void ConnectionToClientHandlerThread::handleIncomingMessage(QVariant message) {
  MainTask* main_task = MainTask::instance();

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
    SetCurrentDirCommand(main_task->appState(), msg->newPath.toStdString()).execute();
  } else if (auto msg = get_if<SetPreviewFileMessage>(&message); msg != nullptr) {
    SetPreviewFileCommand(main_task->appState(), msg->newPath.toStdString()).execute();
  } else {
    qDebug() << "unknown incoming message";
  }
}

#include "ipc/moc_connection_to_client_handler.cpp"
