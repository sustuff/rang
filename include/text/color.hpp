#ifndef RANG_INCLUDE_TEXT_COLOR_HPP_
#define RANG_INCLUDE_TEXT_COLOR_HPP_

#include "term/modifiers.hpp"

class Color {
    quint8 red_;
    quint8 green_;
    quint8 blue_;
    quint8 alpha_;

  public:
    Color();
    Color(quint8 red, quint8 green, quint8 blue, quint8 alpha);

    bool operator==(const Color&) const = default;

    quint8 red() const;
    quint8 green() const;
    quint8 blue() const;
    quint8 alpha() const;

    std::string print(int y) const;
};

#endif  // RANG_INCLUDE_TEXT_COLOR_HPP_
