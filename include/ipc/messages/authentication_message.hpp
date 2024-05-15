#ifndef RANG_INCLUDE_IPC_MESSAGES_AUTHENTICATION_MESSAGE_HPP_
#define RANG_INCLUDE_IPC_MESSAGES_AUTHENTICATION_MESSAGE_HPP_

#include <QMetaType>
#include <QString>

/// The first message that should be sent by client.
struct AuthenticationMessage {
    QString token;
};

QDataStream& operator<<(QDataStream& out, const AuthenticationMessage& msg);
QDataStream& operator>>(QDataStream& in, AuthenticationMessage& msg);

Q_DECLARE_METATYPE(AuthenticationMessage)

#endif  // RANG_INCLUDE_IPC_MESSAGES_AUTHENTICATION_MESSAGE_HPP_
