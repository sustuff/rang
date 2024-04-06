#include "app_info.hpp"
#include "main_task.hpp"

int normalMain(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(AppInfo::appName);
  QCoreApplication::setApplicationVersion(AppInfo::versionString);

  QCommandLineParser parser;
  parser.setApplicationDescription(AppInfo::description);
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption setDirPathOption("set-current-dir", "change current dir", "new-current-dir");
  parser.addOption(setDirPathOption);

  QCommandLineOption authTokenOption("token", "auth token", "token");
  parser.addOption(authTokenOption);

  parser.process(app);

  auto* task = new MainTask(&app);
  QObject::connect(task, &MainTask::finished, &app, &QCoreApplication::quit);
  QTimer::singleShot(0, task, &MainTask::run);

  return QCoreApplication::exec();
}
