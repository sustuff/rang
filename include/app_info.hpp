#ifndef RANG_SRC_APP_INFO_HPP_
#define RANG_SRC_APP_INFO_HPP_

#include <QtCore>
#include "build_timestamp.h"

struct AppInfo {
    inline static QString title = "rang";
    inline static QString versionString = "0.1.0";
    inline static QString description = "Qt-based command line file manager";
    inline static QDateTime buildDate =
        QDateTime::fromSecsSinceEpoch(RANG_BUILD_TIMESTAMP, QTimeZone::utc());
};

#endif  // RANG_SRC_APP_INFO_HPP_
