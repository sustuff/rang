#ifndef RANG_INCLUDE_TEXT_WORD_HPP_
#define RANG_INCLUDE_TEXT_WORD_HPP_

#include "color.hpp"

class Word {
    QString content;
    Color color;

  public:
    Word(const Word&) = default;
    Word(Word&&) = default;
    Word(const QString& content, const Color& color = Color{});
    Word& operator=(const Word&) = default;
    Word& operator=(Word&&) = default;

    bool operator==(const Word&) const = default;

    QString getContent() const;
    Color getColor() const;
    Word getPrefix(quint16 prefixSize) const;

    quint16 size() const;
    bool isEmpty() const;
};

std::weak_ordering operator<=>(const Word&, const Word&);

template <typename CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& stream, const Word& word) {
  return stream << word.getColor() << word.getContent().toStdString();
}

#endif  // RANG_INCLUDE_TEXT_WORD_HPP_
