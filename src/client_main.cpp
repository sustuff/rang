#include "app_info.hpp"
#include "client_task.hpp"
#include "ipc/messages/messages.hpp"

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

  QCommandLineOption setPreviewFileOption("set-preview-file", "change preview file path",
                                          "new-preview-file-path");
  parser.addOption(setPreviewFileOption);

  QCommandLineOption authTokenOption("token", "auth token", "token");
  parser.addOption(authTokenOption);

  parser.process(app);

  QVariant message;
  if (parser.isSet(setDirPathOption)) {
    message = QVariant::fromValue(SetCurrentDirMessage{.newPath = parser.value(setDirPathOption)});
  } else if (parser.isSet(setPreviewFileOption)) {
    message =
        QVariant::fromValue(SetPreviewFileMessage{.newPath = parser.value(setPreviewFileOption)});
  } else {
    parser.showHelp(1);
  }

  auto* task = new ClientTask(&app);
  QObject::connect(task, &ClientTask::finished, &app, &QCoreApplication::quit);
  QTimer::singleShot(0, task, [&]() { task->run(parser.value(authTokenOption), message); });

  return QCoreApplication::exec();
}
