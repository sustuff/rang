#include "buffer/path_buffer.hpp"

void PathBuffer::setPath(std::filesystem::path newPath) {
  m_path = std::move(newPath);
  update();
}

#include "buffer/moc_path_buffer.cpp"
