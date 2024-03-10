#ifndef RANG_SRC_APP_STATE_HPP_
#define RANG_SRC_APP_STATE_HPP_

#include <QtCore>

#include "register/path_register.hpp"

class AppState : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;

    PathRegister currentDir;
    PathRegister previewPath;
    QList<PathRegister> selectedPaths;
};

#endif  // RANG_SRC_APP_STATE_HPP_
