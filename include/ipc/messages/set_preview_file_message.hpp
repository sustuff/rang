#ifndef RANG_INCLUDE_IPC_MESSAGES_SET_PREVIEW_FILE_MESSAGE_HPP_
#define RANG_INCLUDE_IPC_MESSAGES_SET_PREVIEW_FILE_MESSAGE_HPP_

#include <QMetaType>
#include <QString>

/// Tells file manager to change it's current preview file path to newPath.
struct SetPreviewFileMessage {
    QString newPath;
};

QDataStream& operator<<(QDataStream& in, const SetPreviewFileMessage& msg);
QDataStream& operator>>(QDataStream& in, SetPreviewFileMessage& msg);

Q_DECLARE_METATYPE(SetPreviewFileMessage)

#endif  // RANG_INCLUDE_IPC_MESSAGES_SET_PREVIEW_FILE_MESSAGE_HPP_
