#include "buffer/file_list_buffer.hpp"

QVector<QString> FileListBuffer::getLines() {
  QVector<QString> result;

  for (const auto& file_info : fileList) {
    result.append(file_info.fileName());
  }

  return result;
}

void FileListBuffer::update() {
  fileList.clear();
  QDir dir(m_path);
  for (const auto& entry : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name)) {
    fileList.append(entry);
  }
}

#include "buffer/moc_file_list_buffer.cpp"
