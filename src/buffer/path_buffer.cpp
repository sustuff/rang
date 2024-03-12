#include "buffer/path_buffer.hpp"

void PathBuffer::setPath(std::filesystem::path newPath) {
  m_path = std::move(newPath);
}

#include "buffer/moc_path_buffer.cpp"
