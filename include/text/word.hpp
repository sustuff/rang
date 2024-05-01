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

    std::string print() const;

    static Word fromFileInfo(const QFileInfo&);
};

std::weak_ordering operator<=>(const Word&, const Word&);

#endif  // RANG_INCLUDE_TEXT_WORD_HPP_
