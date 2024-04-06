#include "client_task.hpp"
#include "app_info.hpp"
#include "ipc/messages/authentication_message.hpp"
#include "ipc/messages/set_current_dir_message.hpp"

void ClientTask::run(const QString& newPath, const QString& token) {
  qInfo("running %s in client mode (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::buildDate.toString()));

  auto* socket = new QLocalSocket(this);
  connect(socket, &QLocalSocket::connected, this, [this, socket, newPath, token]() {
    qInfo() << "connection succeed";
    QDataStream stream(socket);

    stream << QVariant::fromValue(AuthenticationMessage{.token = token});
    stream << QVariant::fromValue(SetCurrentDirMessage{.newPath = newPath});
    socket->flush();

    emit finished();
  });

  connect(socket, &QLocalSocket::errorOccurred, this,
          [](QLocalSocket::LocalSocketError error) { qInfo() << "error" << error; });
  socket->connectToServer("rang-server");
}

#include "moc_client_task.cpp"
