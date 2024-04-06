#ifndef RANG_SRC_MAIN_TASK_HPP_
#define RANG_SRC_MAIN_TASK_HPP_

#include <QtCore>
#include "app_info.hpp"
#include "app_state.hpp"
#include "buffer/file_info_buffer.hpp"
#include "buffer/file_list_buffer.hpp"
#include "ipc/listener.hpp"

/// Entry point in normal mode.
class MainTask : public QObject {
    Q_OBJECT
  public:
    explicit MainTask(QObject* parent = nullptr);

    MainTask(const MainTask&) = delete;
    MainTask& operator=(const MainTask&) = delete;
    static MainTask* instance();

    LockedAppState appState() const;
    QString getRemoteControlToken() const;

  public slots:
    void run();

  signals:
    void finished();

  private:
    inline static MainTask* self = nullptr;

    AppState* m_appState{};
    mutable QMutex m_mutex{};
    Listener* m_listener{};
    //    QList<Buffer*> bufferList;

    QString m_remoteControlToken{"token123"};
};

#endif  // RANG_SRC_MAIN_TASK_HPP_
