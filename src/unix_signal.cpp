#include "unix_signal.hpp"

namespace unix_signal {
Signal::Signal(int* fileDescriptor, QObject* parent)
    : QObject{parent}, notifier{nullptr}, fileDescriptor{fileDescriptor} {
}

void Signal::handleSignal() {
  notifier->setEnabled(false);
  char tmp;
  read(fileDescriptor[1], &tmp, sizeof(tmp));
  emit received();
  notifier->setEnabled(true);
}
}  // namespace unix_signal

#include "moc_unix_signal.cpp"
