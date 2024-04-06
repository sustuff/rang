#include "app_info.hpp"
#include "client_task.hpp"

int clientMain(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(AppInfo::clientAppName);
  QCoreApplication::setApplicationVersion(AppInfo::versionString);

  QCommandLineParser parser;
  parser.setApplicationDescription(AppInfo::clientDescription);
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption setDirPathOption("set-current-dir", "change current dir", "new-current-dir");
  parser.addOption(setDirPathOption);

  QCommandLineOption authTokenOption("token", "auth token", "token");
  parser.addOption(authTokenOption);

  parser.process(app);

  auto* task = new ClientTask(&app);
  QObject::connect(task, &ClientTask::finished, &app, &QCoreApplication::quit);
  QTimer::singleShot(
      0, task, [&]() { task->run(parser.value(setDirPathOption), parser.value(authTokenOption)); });

  return QCoreApplication::exec();
}