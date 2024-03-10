#ifndef RANG_SRC_APP_INFO_HPP_
#define RANG_SRC_APP_INFO_HPP_

#include <QtCore>
#include "build_timestamp.h"

struct AppInfo {
    inline static QString title = "rang";
    inline static QDateTime build_date =
        QDateTime::fromSecsSinceEpoch(RANG_BUILD_TIMESTAMP, QTimeZone::UTC);
};

#endif  // RANG_SRC_APP_INFO_HPP_
