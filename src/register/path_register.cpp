#include "path_register.hpp"

void PathRegister::setPath(std::filesystem::path new_path) {
  m_path = std::move(new_path);
  emit changed(m_path);
}

const std::filesystem::path& PathRegister::path() const {
  return m_path;
}

QDataStream& operator<<(QDataStream& out, const PathRegister& reg) {
  return out << QString::fromStdString(reg.m_path.string());
}

QDataStream& operator>>(QDataStream& in, PathRegister& reg) {
  QString str;
  in >> str;
  reg.m_path = str.toStdString();
  return in;
}

#include "moc_path_register.cpp"
