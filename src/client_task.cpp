#include "client_task.hpp"
#include "app_info.hpp"

void ClientTask::run() {
  qInfo("running %s in client mode (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::buildDate.toString()));

  auto* socket = new QLocalSocket(this);
  connect(socket, &QLocalSocket::connected, this, [socket]() {
    qInfo() << "connection succeed";
    socket->write("hello\n");
    qInfo() << socket->read(1024);
  });

  connect(socket, &QLocalSocket::errorOccurred, this,
          [socket](QLocalSocket::LocalSocketError error) { qInfo() << "error" << error; });
  socket->connectToServer("rang-m_server");

  // exit on enter, non-blocking
  auto* notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, this, &ClientTask::finished);
}

#include "moc_client_task.cpp"
