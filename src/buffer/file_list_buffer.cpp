#include "buffer/file_list_buffer.hpp"

QVector<Line> FileListBuffer::getLines() {
  QVector<Line> result;

  for (const auto& fileInfo : fileList) {
    result.append(Word::fromFileInfo(fileInfo));
  }

  return result;
}

void FileListBuffer::update() {
  fileList.clear();
  QDir dir(m_path);
  for (const auto& entry : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name)) {
    fileList.append(entry);
  }
  emit contentChanged();
}

#include "buffer/moc_file_list_buffer.cpp"
