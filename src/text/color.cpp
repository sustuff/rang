#include "text/color.hpp"
#include "term/manip.hpp"

Color::Color() : red_{0}, green_{0}, blue_{0}, alpha_{0}, isDefault_{true} {
}

Color::Color(quint8 red, quint8 green, quint8 blue, quint8 alpha)
    : red_{red}, green_{green}, blue_{blue}, alpha_{alpha}, isDefault_{false} {
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

bool Color::isDefault() const {
  return isDefault_;
}

std::string Color::print() const {
  if (isDefault_) {
    return term::manip::reset_color;
  }
  return term::manip::true_color(false, red_, green_, blue_);
}

const Color Color::DIR_COLOR{38, 139, 210, 255};
const Color Color::EXECUTABLE_COLOR{133, 153, 0, 255};

Color Color::fromFileInfo(const QFileInfo& fileInfo) {
  if (fileInfo.isDir()) {
    return DIR_COLOR;
  }
  if (fileInfo.isExecutable()) {
    return EXECUTABLE_COLOR;
  }
  return {};
}
