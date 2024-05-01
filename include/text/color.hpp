#ifndef RANG_INCLUDE_TEXT_COLOR_HPP_
#define RANG_INCLUDE_TEXT_COLOR_HPP_

#include <QFileInfo>

class Color {
    quint8 red_;
    quint8 green_;
    quint8 blue_;
    quint8 alpha_;
    bool isDefault_;

  public:
    Color();
    Color(quint8 red, quint8 green, quint8 blue, quint8 alpha);

    bool operator==(const Color&) const = default;

    quint8 red() const;
    quint8 green() const;
    quint8 blue() const;
    quint8 alpha() const;
    bool isDefault() const;

    std::string print(bool background) const;

    static const Color WHITE;
    static const Color DIR_COLOR;
    static const Color EXECUTABLE_COLOR;
    static const Color HIGHLIGHTED_COLOR;
    static Color fromFileInfo(const QFileInfo&, bool background);
};

#endif  // RANG_INCLUDE_TEXT_COLOR_HPP_
