#include "app_state.hpp"

LockedAppState::LockedAppState(LockedAppState&& other) noexcept
    : state(other.state), lock(std::move(other.lock)) {
}

LockedAppState& LockedAppState::operator=(LockedAppState&& other) noexcept {
  state = other.state;
  lock = std::move(other.lock);
  return *this;
}

AppState* LockedAppState::operator->() {
  return state;
}

const AppState* LockedAppState::operator->() const {
  return state;
}

AppState& LockedAppState::operator*() {
  return *state;
}

const AppState& LockedAppState::operator*() const {
  return *state;
}

LockedAppState::LockedAppState(AppState* state, QMutex* mutex) : state(state), lock(mutex) {
}

#include "moc_app_state.cpp"
