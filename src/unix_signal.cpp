#include "unix_signal.hpp"

UnixSignal::UnixSignal(int* fileDescriptor, QObject* parent)
    : QObject{parent}, notifier{nullptr}, fileDescriptor{fileDescriptor} {
}

void UnixSignal::handleSignal() {
  notifier->setEnabled(false);
  char tmp;
  read(fileDescriptor[1], &tmp, sizeof(tmp));
  emit received();
  notifier->setEnabled(true);
}

#include "moc_unix_signal.cpp"
