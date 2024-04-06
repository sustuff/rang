#ifndef RANG_SRC_APP_INFO_HPP_
#define RANG_SRC_APP_INFO_HPP_

#include <QtCore>
#include "build_config.hpp"

struct AppInfo {
    inline static QString appName = RANG_APP_NAME;
    inline static QString clientAppName = RANG_CLIENT_APP_NAME;
    inline static QString versionString = RANG_VERSION_STRING;
    inline static QString description = "Qt-based terminal file manager.";
    inline static QString clientDescription = "Control running " RANG_APP_NAME " instance.";
    inline static QDateTime buildDate =
        QDateTime::fromSecsSinceEpoch(RANG_BUILD_TIMESTAMP, QTimeZone::utc());
};

#endif  // RANG_SRC_APP_INFO_HPP_
