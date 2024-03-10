#include "main_task.hpp"

#include "app_info.hpp"
#include "app_state.hpp"
#include "buffer/file_info_buffer.hpp"
#include "buffer/file_list_buffer.hpp"

MainTask::MainTask(QObject* parent) : QObject(parent) {
}

void MainTask::run() {
  qInfo("running %s (built %s)", qUtf8Printable(AppInfo::title),
        qUtf8Printable(AppInfo::build_date.toString()));

  auto* state = new AppState();
  auto* file_list_buffer = new FileListBuffer();
  auto* preview_buffer = new FileInfoBuffer();

  connect(&state->current_dir, &PathRegister::changed, file_list_buffer,
          [=](const QFileInfo& file) { file_list_buffer->setPath(file.filesystemFilePath()); });
  connect(&state->preview_path, &PathRegister::changed, preview_buffer,
          [=](const QFileInfo& file) { preview_buffer->setPath(file.filesystemFilePath()); });

  auto draw = [&]() {
    file_list_buffer->update();
    preview_buffer->update();

    auto list1 = file_list_buffer->getLines();
    auto list2 = preview_buffer->getLines();
    QString result;
    qsizetype n = qMax(list1.size(), list2.size());
    for (qsizetype i = 0; i < n; ++i) {
      result +=
          (list1.value(i, "").leftJustified(80) + " | " + list2.value(i, "").leftJustified(80)) +
          "\n";
    }
    qInfo(
        "======================================================== listing ???? "
        "========================================================\n%s",
        qUtf8Printable(result));
  };

  state->current_dir.setPath(QFileInfo("../src"));
  state->preview_path.setPath(QFileInfo("../src/main.cpp"));
  draw();

  emit finished();
}

#include "moc_main_task.cpp"
