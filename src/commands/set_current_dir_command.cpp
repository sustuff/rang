#include "commands/set_current_dir_command.hpp"

#include <utility>

void SetCurrentDirCommand::execute() {
  QMutexLocker lock(&m_state->mutex);

  auto newPathCanonical = canonical(m_newPath);
  current_path(newPathCanonical);
  m_state->currentDir.setPath(newPathCanonical);
  m_state->previewPath.setPath("");
}

SetCurrentDirCommand::SetCurrentDirCommand(AppState* state, std::filesystem::path newPath)
    : Command(state), m_newPath(std::move(newPath)) {
}
