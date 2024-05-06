#include "buffer/file_list_buffer.hpp"
#include <QDir>

QVector<Line> FileListBuffer::getLines() {
  QVector<Line> result;

  for (const auto& fileInfo : fileList) {
    result.append(Word::fromFileInfo(fileInfo, result.size() == currentFile));
  }

  return result;
}

std::optional<std::filesystem::path> FileListBuffer::getCurrentFile() const {
  if (fileList.isEmpty()) {
    return std::nullopt;
  }
  return fileList[currentFile].filesystemAbsoluteFilePath();
}

void FileListBuffer::update() {
  fileList.clear();
  QDir dir(m_path);
  for (const auto& entry : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name)) {
    fileList.append(entry);
  }
  if (currentFile >= fileList.size()) {
    currentFile = fileList.isEmpty() ? 0 : fileList.size() - 1;
  }
  sendUpdates();
}

void FileListBuffer::goDown() {
  if (currentFile + 1 < fileList.size()) {
    ++currentFile;
    sendUpdates();
  }
}

void FileListBuffer::goUp() {
  if (currentFile > 0) {
    --currentFile;
    sendUpdates();
  }
}

void FileListBuffer::sendUpdates() {
  emit contentChanged();
  emit currentFileChanged(getCurrentFile());
}

#include "buffer/moc_file_list_buffer.cpp"
