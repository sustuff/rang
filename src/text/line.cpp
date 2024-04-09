#include "text/line.hpp"
#include "qt_operators.hpp"

Line::Line(const QString& content) : QVector<Word>{content} {
}

Line::Line(const char* content) : Line{QString{content}} {
}

Line Line::getPrefix(quint16 size) const {
  Line newLine;
  for (const Word& word : *this) {
    Word newWord = word.getPrefix(size);
    if (newWord.isEmpty()) {
      break;
    }
    size -= newWord.size();
    newLine.emplaceBack(std::move(newWord));
  }
  return newLine;
}
