#include "file_list_buffer.hpp"

QVector<QString> FileListBuffer::getLines() {
  QVector<QString> result;

  for (const auto& file_info : fileList) {
    result.append(file_info.fileName());
  }

  return result;
}

void FileListBuffer::update() {
  fileList.clear();
  for (const auto& entry : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
    fileList.append(entry);
  }
}

void FileListBuffer::setPath(const std::filesystem::path& newPath) {
  dir = newPath;
}

#include "moc_file_list_buffer.cpp"
