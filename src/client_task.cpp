#include "client_task.hpp"
#include "app_info.hpp"
#include "ipc/messages/messages.hpp"

void ClientTask::run(const QString& token, const QVariant& message) {
  auto* socket = new QLocalSocket(this);
  connect(socket, &QLocalSocket::connected, this, [=, this]() {
    QDataStream stream(socket);

    stream << QVariant::fromValue(AuthenticationMessage{.token = token});
    stream << message;
    socket->flush();

    emit finished();
  });

  connect(socket, &QLocalSocket::errorOccurred, this,
          [](QLocalSocket::LocalSocketError error) { qInfo() << "error" << error; });
  socket->connectToServer("rang-server");
}

#include "moc_client_task.cpp"
