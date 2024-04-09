#ifndef RANG_INCLUDE_TEXT_LINE_HPP_
#define RANG_INCLUDE_TEXT_LINE_HPP_

#include "word.hpp"

class Line : public QVector<Word> {
  public:
    Line() = default;
    Line(const Line&) = default;
    Line(Line&&) = default;
    Line(const QString&);
    Line(const char*);
    Line& operator=(const Line&) = default;
    Line& operator=(Line&&) = default;

    bool operator==(const Line&) const = default;

    Line getPrefix(quint16 prefixSize) const;
};

#endif  // RANG_INCLUDE_TEXT_LINE_HPP_
