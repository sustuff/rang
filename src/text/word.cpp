#include "text/word.hpp"
#include "qt_operators.hpp"
#include "term/modifiers.hpp"

Word::Word(const QString& content, const Color& color) : content{content}, color{color} {
}

QString Word::getContent() const {
  return content;
}

Color Word::getColor() const {
  return color;
}

Word Word::getPrefix(quint16 prefixSize) const {
  if (prefixSize >= size()) {
    return *this;
  }
  return Word{content.leftJustified(prefixSize, '#', true), color};
}

quint16 Word::size() const {
  return content.size();
}

bool Word::isEmpty() const {
  return content.isEmpty();
}

std::string Word::print(int y) const {
  return color.print(y) + content.toStdString() + term::modifiers::reset_color;
}

std::weak_ordering operator<=>(const Word& left, const Word& right) {
  return left.getContent() <=> right.getContent();
}
