#include "path_buffer.hpp"

void PathBuffer::setPath(std::filesystem::path newPath) {
  m_path = std::move(newPath);
}

#include "moc_path_buffer.cpp"
