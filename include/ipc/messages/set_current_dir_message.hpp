#ifndef RANG_SRC_IPC_MESSAGES_SET_CURRENT_DIR_MESSAGE_HPP_
#define RANG_SRC_IPC_MESSAGES_SET_CURRENT_DIR_MESSAGE_HPP_

/// Tells file manager to change it's current dir to newPath.
struct SetCurrentDirMessage {
    QString newPath;
};

QDataStream& operator<<(QDataStream& in, const SetCurrentDirMessage& reg);
QDataStream& operator>>(QDataStream& in, SetCurrentDirMessage& reg);

Q_DECLARE_METATYPE(SetCurrentDirMessage)

#endif  // RANG_SRC_IPC_MESSAGES_SET_CURRENT_DIR_MESSAGE_HPP_
