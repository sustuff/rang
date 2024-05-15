#include "meta.hpp"

#include "ipc/messages/messages.hpp"

void register_qt_metatypes() {
  qRegisterMetaType<SetCurrentDirMessage>();
  qRegisterMetaType<AuthenticationMessage>();
  qRegisterMetaType<SetPreviewFileMessage>();
}
