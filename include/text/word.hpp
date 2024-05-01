#ifndef RANG_INCLUDE_TEXT_WORD_HPP_
#define RANG_INCLUDE_TEXT_WORD_HPP_

#include "color.hpp"

class Word {
    QString content;
    Color color;
    Color backgroundColor;

  public:
    Word(QString content, Color color = Color{}, Color backgroundColor = Color{});

    bool operator==(const Word&) const = default;

    QString getContent() const;
    void setContent(QString);
    Color getColor() const;
    void setColor(Color);
    Color getBackgroundColor() const;
    void setBackgroundColor(Color);
    Word getPrefix(quint16 prefixSize) const;

    quint16 size() const;
    bool isEmpty() const;

    std::string print() const;

    static Word fromFileInfo(const QFileInfo&, bool selected);
};

std::weak_ordering operator<=>(const Word&, const Word&);

#endif  // RANG_INCLUDE_TEXT_WORD_HPP_
