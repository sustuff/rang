#include "buffer/file_info_buffer.hpp"

QVector<QString> FileInfoBuffer::getLines() {
  QVector<QString> result;

  if (fileInfo.absoluteFilePath().isEmpty()) {
    result.append("no file selected");
  } else {
    result.append(fileInfo.absoluteFilePath());
    result.append("owned by " + fileInfo.owner());
    result.append("last modified at " + fileInfo.lastModified().toString());
  }

  return result;
}

void FileInfoBuffer::update() {
  fileInfo = QFileInfo(m_path);
}

#include "buffer/moc_file_info_buffer.cpp"
