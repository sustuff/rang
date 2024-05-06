#ifndef RANG_SRC_APP_STATE_HPP_
#define RANG_SRC_APP_STATE_HPP_

#include <QMutex>
#include <filesystem>

#include "register/path_register.hpp"

/// AppState is a shared instance with global app properties.
class AppState : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

    PathRegister currentDir;
    PathRegister previewPath;
    QList<PathRegister> selectedPaths;

    mutable QMutex mutex;

  signals:
    void finished();

  public slots:
    void setPreviewPath(std::optional<std::filesystem::path>);
};

#endif  // RANG_SRC_APP_STATE_HPP_
