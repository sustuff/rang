#ifndef RANG_SRC_UNIX_SIGNAL_HPP_
#define RANG_SRC_UNIX_SIGNAL_HPP_

#include <signal.h>
#include <QObject>
#include <QSocketNotifier>

class UnixSignal : public QObject {
    Q_OBJECT
  public:
    explicit UnixSignal(int signalNumber, QObject* parent = nullptr);

  signals:
    void received();

  private:
    static void signalHandler(int);

    static inline int fileDescriptor[2];
    QSocketNotifier* notifier;

  private slots:
    void handleSignal();
};

#endif  // RANG_SRC_UNIX_SIGNAL_HPP_
