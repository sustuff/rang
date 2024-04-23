#ifndef RANG_INCLUDE_TEXT_LINE_HPP_
#define RANG_INCLUDE_TEXT_LINE_HPP_

#include "word.hpp"

class Line {
    QVector<Word> words;

  public:
    Line() = default;
    Line(const Line&) = default;
    Line(Line&&) = default;
    Line(const QString&);
    Line(const char*);
    Line& operator=(const Line&) = default;
    Line& operator=(Line&&) = default;

    bool operator==(const Line&) const = default;

    const QVector<Word>& getWords() const;
    Line getPrefix(quint16 prefixSize) const;

    template <typename... Args>
    void emplaceBack(Args&&... args);
};

std::weak_ordering operator<=>(const Line&, const Line&);

#endif  // RANG_INCLUDE_TEXT_LINE_HPP_
