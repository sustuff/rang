#ifndef RANG_INCLUDE_COMPATIBILITY_HPP_
#define RANG_INCLUDE_COMPATIBILITY_HPP_

#include <QVariant>

#if QT_VERSION < 0x060600

// since Qt 6.6

template <typename T>
T* get_if(QVariant* v) noexcept {
  // data() will detach from is_null, returning non-nullptr
  if (!v || v->metaType() != QMetaType::fromType<T>())
    return nullptr;
  return static_cast<T*>(v->data());
}
#endif

#endif  // RANG_INCLUDE_COMPATIBILITY_HPP_
