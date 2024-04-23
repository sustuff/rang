#include "text/color.hpp"
#include "term/manip.hpp"

Color::Color() : Color{255, 255, 255, 255} {
}

Color::Color(quint8 red, quint8 green, quint8 blue, quint8 alpha)
    : red_{red}, green_{green}, blue_{blue}, alpha_{alpha} {
}

quint8 Color::red() const {
  return red_;
}

quint8 Color::green() const {
  return green_;
}

quint8 Color::blue() const {
  return blue_;
}

quint8 Color::alpha() const {
  return alpha_;
}

std::string Color::print() const {
  return term::manip::true_color(false, red_, green_, blue_);
}
