#ifndef RANG_SRC_REGISTER_PATH_REGISTER_HPP_
#define RANG_SRC_REGISTER_PATH_REGISTER_HPP_

#include "register.hpp"
#include <filesystem>

class PathRegister : public Register {
    Q_OBJECT
  public:
    using Register::Register;

    Q_PROPERTY(std::filesystem::path path READ path WRITE setPath NOTIFY changed);

    const std::filesystem::path& path() const;

    void setPath(std::filesystem::path new_path);

    friend QDataStream& operator<<(QDataStream& in, const PathRegister& reg);
    friend QDataStream& operator>>(QDataStream& in, PathRegister& reg);

  signals:
    void changed(const std::filesystem::path&);

  private:
    std::filesystem::path m_path;
};

#endif  // RANG_SRC_REGISTER_PATH_REGISTER_HPP_
