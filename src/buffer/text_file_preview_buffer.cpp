#include "buffer/text_file_preview_buffer.hpp"

void TextFilePreviewBuffer::update() {
  if (!m_path.empty()) {
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    fileContent = file.readAll();
  } else {
    fileContent = "";
  }
}

QVector<QString> TextFilePreviewBuffer::getLines() {
  return fileContent.split('\n');
}

#include "buffer/moc_text_file_preview_buffer.cpp"
