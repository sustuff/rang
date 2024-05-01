#include "buffer/text_file_preview_buffer.hpp"

void TextFilePreviewBuffer::update() {
  namespace fs = std::filesystem;
  if (fs::status(m_path).type() == fs::file_type::regular) {
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    fileContent = file.readAll();
    normalizeFileContent();
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

void TextFilePreviewBuffer::normalizeFileContent() {
  QString oldFileContent = std::move(fileContent);
  fileContent.clear();
  fileContent.reserve(oldFileContent.size());
  for (const QChar& ch : oldFileContent) {
    if (ch == '\t') {
      fileContent.append("  ");
    } else if (ch == '\n' || (' ' <= ch && ch <= '~')) {
      fileContent.append(ch);
    } else if (ch != '\r') {
      fileContent.clear();
      break;
    }
  }
}

#include "buffer/moc_text_file_preview_buffer.cpp"
