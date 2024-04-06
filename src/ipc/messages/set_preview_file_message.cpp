#include "ipc/messages/set_preview_file_message.hpp"

QDataStream& operator<<(QDataStream& out, const SetPreviewFileMessage& msg) {
  out << msg.newPath;
  return out;
}

QDataStream& operator>>(QDataStream& in, SetPreviewFileMessage& msg) {
  in >> msg.newPath;
  return in;
}
