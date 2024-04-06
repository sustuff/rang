#ifndef RANG_INCLUDE_REGISTER_CURRENT_DIR_REGISTER_HPP_
#define RANG_INCLUDE_REGISTER_CURRENT_DIR_REGISTER_HPP_

#include "path_register.hpp"

class CurrentDirRegister : public PathRegister {
    Q_OBJECT
  public:
    using PathRegister::PathRegister;

    Q_PROPERTY(std::filesystem::path path READ path WRITE setPath NOTIFY changed);

    void setPath(const std::filesystem::path& newPath);

  signals:
    void changed(const std::filesystem::path&);
};

#endif  // RANG_INCLUDE_REGISTER_CURRENT_DIR_REGISTER_HPP_
