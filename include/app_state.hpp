#ifndef RANG_SRC_APP_STATE_HPP_
#define RANG_SRC_APP_STATE_HPP_

#include <QtCore>

#include "register/path_register.hpp"

/// AppState is a shared instance with global app properties.
class AppState : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

    PathRegister currentDir;
    PathRegister previewPath;
    QList<PathRegister> selectedPaths;
};

struct LockedAppState {
    AppState* state;
    QMutexLocker<QMutex> lock;

    LockedAppState(AppState* state, QMutex* mutex);

    LockedAppState(const LockedAppState&) = delete;
    LockedAppState& operator=(const LockedAppState&) = delete;
    LockedAppState(LockedAppState&& other) noexcept;
    LockedAppState& operator=(LockedAppState&& other) noexcept;
    ~LockedAppState() = default;

    AppState& operator*();
    AppState* operator->();
    const AppState& operator*() const;
    const AppState* operator->() const;
};

#endif  // RANG_SRC_APP_STATE_HPP_
