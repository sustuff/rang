#include "file_info_buffer.hpp"

QVector<QString> FileInfoBuffer::getLines() {
  QVector<QString> result;

  result.append(fileInfo.absoluteFilePath());
  result.append("owned by " + fileInfo.owner());
  result.append("last modified at " + fileInfo.lastModified().toString());

  return result;
}

void FileInfoBuffer::update() {
  fileInfo = QFileInfo(path);
}

void FileInfoBuffer::setPath(std::filesystem::path newPath) {
  path = std::move(newPath);
}

#include "moc_file_info_buffer.cpp"