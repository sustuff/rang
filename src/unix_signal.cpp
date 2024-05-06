#include "unix_signal.hpp"
#include <sys/socket.h>

UnixSignal::UnixSignal(int signalNumber, QObject* parent) : QObject{parent} {
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fileDescriptor)) {
    qFatal("Couldn't create socketpair for signal %d", signalNumber);
  }
  notifier = new QSocketNotifier(fileDescriptor[1], QSocketNotifier::Read, this);
  connect(notifier, &QSocketNotifier::activated, this, &UnixSignal::handleSignal);

  struct sigaction action;
  action.sa_handler = UnixSignal::signalHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  if (sigaction(signalNumber, &action, 0)) {
    qFatal("Couldn't setup handler for signal %d", signalNumber);
  }
}

void UnixSignal::signalHandler(int) {
  char tmp = 1;
  write(fileDescriptor[0], &tmp, sizeof(tmp));
}

void UnixSignal::handleSignal() {
  notifier->setEnabled(false);
  char tmp;
  read(fileDescriptor[1], &tmp, sizeof(tmp));
  emit received();
  notifier->setEnabled(true);
}

#include "moc_unix_signal.cpp"
