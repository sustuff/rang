#include "app_state.hpp"

void AppState::setPreviewPath(std::optional<std::filesystem::path> newPreviewPath) {
  if (newPreviewPath.has_value()) {
    previewPath.setPath(std::move(newPreviewPath.value()));
  }
}

#include "moc_app_state.cpp"
