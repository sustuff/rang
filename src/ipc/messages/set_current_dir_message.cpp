#include "ipc/messages/set_current_dir_message.hpp"

QDataStream& operator<<(QDataStream& out, const SetCurrentDirMessage& reg) {
  out << reg.newPath;
  return out;
}

QDataStream& operator>>(QDataStream& in, SetCurrentDirMessage& reg) {
  in >> reg.newPath;
  return in;
}
