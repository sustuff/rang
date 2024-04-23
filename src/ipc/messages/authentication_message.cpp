#include "ipc/messages/authentication_message.hpp"

QDataStream& operator<<(QDataStream& out, const AuthenticationMessage& msg) {
  out << msg.token;
  return out;
}

QDataStream& operator>>(QDataStream& in, AuthenticationMessage& msg) {
  in >> msg.token;
  return in;
}
