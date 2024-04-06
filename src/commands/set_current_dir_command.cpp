#include "commands/set_current_dir_command.hpp"

void SetCurrentDirCommand::execute(const std::filesystem::path& newPath) {
  QMutexLocker lock(&m_state->mutex);

  auto newPathCanonical = canonical(newPath);
  current_path(newPathCanonical);
  m_state->currentDir.setPath(newPathCanonical);
  m_state->previewPath.setPath("");
}
