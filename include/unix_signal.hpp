#ifndef RANG_SRC_UNIX_SIGNAL_HPP_
#define RANG_SRC_UNIX_SIGNAL_HPP_

#include <signal.h>
#include <sys/socket.h>
#include <QObject>
#include <QSocketNotifier>

template <int SignalNumber>
class StaticSignalStorage final {
  public:
    StaticSignalStorage() = delete;

    static inline int fileDescriptor[2];

    static void handler(int) {
      char tmp = 1;
      write(fileDescriptor[0], &tmp, sizeof(tmp));
    }
};

class UnixSignal : public QObject {
    Q_OBJECT
  public:
    template <int SignalNumber>
    static UnixSignal* createSelf(QObject* parent) {
      using StaticStorage = StaticSignalStorage<SignalNumber>;
      if (socketpair(AF_UNIX, SOCK_STREAM, 0, StaticStorage::fileDescriptor)) {
        qFatal("Couldn't create socketpair for signal %d", SignalNumber);
      }

      auto* self = new UnixSignal(StaticStorage::fileDescriptor, parent);
      self->notifier = new QSocketNotifier(self->fileDescriptor[1], QSocketNotifier::Read, self);
      connect(self->notifier, &QSocketNotifier::activated, self, &UnixSignal::handleSignal);

      struct sigaction action;
      action.sa_handler = StaticStorage::handler;
      sigemptyset(&action.sa_mask);
      action.sa_flags = SA_RESTART;

      if (sigaction(SignalNumber, &action, 0)) {
        qFatal("Couldn't setup handler for signal %d", SignalNumber);
      }

      return self;
    }

  signals:
    void received();

  private:
    UnixSignal(int* fileDescriptor, QObject* parent);

    QSocketNotifier* notifier;
    int* fileDescriptor;

  private slots:
    void handleSignal();
};

#endif  // RANG_SRC_UNIX_SIGNAL_HPP_
