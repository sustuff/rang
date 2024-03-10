#include "path_register.hpp"

void PathRegister::setPath(std::filesystem::path new_path) {
  m_path = std::move(new_path);
  emit changed(m_path);
}

const std::filesystem::path& PathRegister::path() const {
  return m_path;
}

#include "moc_path_register.cpp"
