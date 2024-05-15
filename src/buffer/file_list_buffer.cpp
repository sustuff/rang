#include "buffer/file_list_buffer.hpp"
#include <QDir>

QVector<Line> FileListBuffer::getLines() {
  QVector<Line> result;

  for (const auto& fileInfo : fileList) {
    result.append(Word::fromFileInfo(fileInfo, result.size() == selectedFile));
  }

  return result;
}

std::optional<std::filesystem::path> FileListBuffer::getSelectedFile() const {
  if (fileList.isEmpty()) {
    return std::nullopt;
  }
  return fileList[selectedFile].filesystemAbsoluteFilePath();
}

void FileListBuffer::update() {
  fileList.clear();
  QDir dir(m_path);
  for (const auto& entry : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name)) {
    fileList.append(entry);
  }
  if (selectedFile >= fileList.size()) {
    selectedFile = fileList.isEmpty() ? 0 : fileList.size() - 1;
  }
  sendUpdates();
}

void FileListBuffer::goDown() {
  if (selectedFile + 1 < fileList.size()) {
    ++selectedFile;
    sendUpdates();
  }
}

void FileListBuffer::goUp() {
  if (selectedFile > 0) {
    --selectedFile;
    sendUpdates();
  }
}

void FileListBuffer::sendUpdates() {
  emit contentChanged();
  emit selectedFileChanged(getSelectedFile());
}

#include "buffer/moc_file_list_buffer.cpp"
