#ifndef RANG_INCLUDE_QT_OPERATORS_HPP_
#define RANG_INCLUDE_QT_OPERATORS_HPP_

#include <QtCore>
#include <algorithm>

std::strong_ordering operator<=>(const QString& left, const QString& right);

template <typename T>
auto operator<=>(const QList<T>& left, const QList<T>& right) {
  return std::lexicographical_compare_three_way(left.cbegin(), left.cend(), right.cbegin(),
                                                right.cend());
}

#endif  // RANG_INCLUDE_QT_OPERATORS_HPP_
