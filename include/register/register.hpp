#ifndef RANG_SRC_REGISTER_REGISTER_HPP_
#define RANG_SRC_REGISTER_REGISTER_HPP_

#include <QtCore>

/// Registers are parts of AppState, they store public information like current directory
/// or list of selected files.
class Register : public QObject {
    Q_OBJECT
  public:
    using QObject::QObject;
};

#endif  // RANG_SRC_REGISTER_REGISTER_HPP_
