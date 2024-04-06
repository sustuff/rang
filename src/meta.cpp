#include "meta.hpp"
#include <QMetaType>

#include "ipc/messages/messages.hpp"

void register_qt_metatypes() {
  qRegisterMetaType<SetCurrentDirMessage>();
  qRegisterMetaType<AuthenticationMessage>();
  qRegisterMetaType<SetPreviewFileMessage>();
}
