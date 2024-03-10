#include "text_file_preview_buffer.hpp"

void TextFilePreviewBuffer::update() {
  QFile file(m_path);
  file.open(QIODevice::ReadOnly);
  fileContent = file.readAll();
}

QVector<QString> TextFilePreviewBuffer::getLines() {
  return fileContent.split('\n');
}

#include "moc_text_file_preview_buffer.cpp"
