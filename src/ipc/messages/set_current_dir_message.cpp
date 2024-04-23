#include "ipc/messages/set_current_dir_message.hpp"

QDataStream& operator<<(QDataStream& out, const SetCurrentDirMessage& msg) {
  out << msg.newPath;
  return out;
}

QDataStream& operator>>(QDataStream& in, SetCurrentDirMessage& msg) {
  in >> msg.newPath;
  return in;
}
