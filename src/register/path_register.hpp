#ifndef RANG_SRC_REGISTER_PATH_REGISTER_HPP_
#define RANG_SRC_REGISTER_PATH_REGISTER_HPP_

#include "register.hpp"

class PathRegister : public Register {
    Q_OBJECT
  public:
    using Register::Register;

    Q_PROPERTY(QFileInfo path READ path WRITE setPath NOTIFY changed);

    const QFileInfo& path() const;

    void setPath(QFileInfo new_path);

  signals:
    void changed(const QFileInfo&);

  private:
    QFileInfo m_path;
};

#endif  // RANG_SRC_REGISTER_PATH_REGISTER_HPP_
