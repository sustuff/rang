#include "text/word.hpp"
#include "qt_operators.hpp"
#include "term/manip.hpp"

Word::Word(QString content, Color color, Color backgroundColor)
    : content{std::move(content)},
      color{std::move(color)},
      backgroundColor{std::move(backgroundColor)} {
}

QString Word::getContent() const {
  return content;
}

void Word::setContent(QString newContent) {
  content = std::move(newContent);
}

Color Word::getColor() const {
  return color;
}

void Word::setColor(Color newColor) {
  color = std::move(newColor);
}

Color Word::getBackgroundColor() const {
  return backgroundColor;
}

void Word::setBackgroundColor(Color newBackgroundColor) {
  backgroundColor = std::move(newBackgroundColor);
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

std::string Word::print() const {
  std::string colorManip;
  if (color.isDefault()) {
    colorManip += color.print(false);
    colorManip += backgroundColor.print(true);
  } else {
    colorManip += backgroundColor.print(true);
    colorManip += color.print(false);
  }
  return colorManip + content.toStdString() + term::manip::reset_color;
}

Word Word::fromFileInfo(const QFileInfo& fileInfo, bool selected) {
  Color color = selected ? Color::WHITE : Color::fromFileInfo(fileInfo, false);
  Color backgroundColor = selected ? Color::fromFileInfo(fileInfo, true) : Color{};
  return Word{fileInfo.fileName(), std::move(color), std::move(backgroundColor)};
}

std::weak_ordering operator<=>(const Word& left, const Word& right) {
  return left.getContent() <=> right.getContent();
}
