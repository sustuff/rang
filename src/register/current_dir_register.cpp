#include "register/current_dir_register.hpp"

void CurrentDirRegister::setPath(const std::filesystem::path& newPath) {
  PathRegister::setPath(newPath.empty() ? "" : canonical(newPath));
}

#include "register/moc_current_dir_register.cpp"
