#include <QtCore>

#include "app_info.hpp"
#include "client_task.hpp"
#include "main_task.hpp"
#include "meta.hpp"

int main(int argc, char* argv[]) {
  register_qt_metatypes();

  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(AppInfo::title);
  QCoreApplication::setApplicationVersion(AppInfo::versionString);

  QCommandLineParser parser;
  parser.setApplicationDescription(AppInfo::description);
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption clientModeOption("client-mode", "run in client mode");
  parser.addOption(clientModeOption);

  QCommandLineOption setDirPathOption("set-current-dir", "change current dir", "new-current-dir");
  parser.addOption(setDirPathOption);

  QCommandLineOption authTokenOption("token", "auth token", "token");
  parser.addOption(authTokenOption);

  parser.process(app);

  const bool clientMode = parser.isSet(clientModeOption);

  if (clientMode) {
    auto* task = new ClientTask(&app);
    QObject::connect(task, &ClientTask::finished, &app, &QCoreApplication::quit);
    QTimer::singleShot(0, task, [&]() {
      task->run(parser.value(setDirPathOption), parser.value(authTokenOption));
    });

  } else {
    auto* task = new MainTask(&app);
    QObject::connect(task, &MainTask::finished, &app, &QCoreApplication::quit);
    QTimer::singleShot(0, task, &MainTask::run);
  }

  return QCoreApplication::exec();
}
