#include "text/line.hpp"
#include "qt_operators.hpp"

Line::Line(const QString& content) : words{content} {
}

Line::Line(const char* content) : Line{QString{content}} {
}

const QVector<Word>& Line::getWords() const {
  return words;
}

Line Line::getPrefix(quint16 size) const {
  Line newLine;
  for (const Word& word : words) {
    Word newWord = word.getPrefix(size);
    if (newWord.isEmpty()) {
      break;
    }
    size -= newWord.size();
    newLine.emplaceBack(std::move(newWord));
  }
  return newLine;
}

template <typename... Args>
void Line::emplaceBack(Args&&... args) {
  words.emplace_back(std::forward<Args>(args)...);
}

std::weak_ordering operator<=>(const Line& left, const Line& right) {
  return left.getWords() <=> right.getWords();
}
