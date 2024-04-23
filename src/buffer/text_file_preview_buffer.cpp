#include "buffer/text_file_preview_buffer.hpp"

void TextFilePreviewBuffer::update() {
  if (!m_path.empty()) {
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    fileContent = file.readAll();
  } else {
    fileContent = "";
  }
  emit contentChanged();
}

QVector<Line> TextFilePreviewBuffer::getLines() {
  QVector<Line> lines;
  for (const QString& fileLine : fileContent.split('\n')) {
    lines.emplace_back(fileLine);
  }
  return lines;
}

#include "buffer/moc_text_file_preview_buffer.cpp"
