#include "commands/set_preview_file_command.hpp"

void SetPreviewFileCommand::execute(const std::filesystem::path& newPath) {
  QMutexLocker lock(&m_state->mutex);

  m_state->previewPath.setPath(newPath);
}
