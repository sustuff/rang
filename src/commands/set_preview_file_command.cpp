#include "commands/set_preview_file_command.hpp"

#include <utility>

void SetPreviewFileCommand::execute() {
  QMutexLocker lock(&m_state->mutex);

  m_state->previewPath.setPath(m_newPath);
}

SetPreviewFileCommand::SetPreviewFileCommand(AppState* state, std::filesystem::path newPath)
    : Command(state), m_newPath(std::move(newPath)) {
}
