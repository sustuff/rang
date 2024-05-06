#include "renderer/renderer.hpp"

Renderer::Renderer(std::unique_ptr<term::window> window, QObject* parent)
    : QObject(parent), m_window(std::move(window)) {
}

void Renderer::changeDimensions(const term::window_dimensions& dims) {
  m_window->change_dimensions(dims);
}


#include "renderer/moc_renderer.cpp"
