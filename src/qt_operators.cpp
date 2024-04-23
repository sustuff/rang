#include "qt_operators.hpp"

std::strong_ordering operator<=>(const QString& left, const QString& right) {
  return left.compare(right) <=> 0;
}
