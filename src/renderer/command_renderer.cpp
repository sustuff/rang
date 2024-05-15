#include "renderer/command_renderer.hpp"
#include <iostream>
#include "term/manip.hpp"

CommandRenderer::CommandRenderer(std::unique_ptr<term::window> window, QObject* parent)
    : Renderer(std::move(window), parent) {
}

// FIXME: Кажется тут немного копипасты
void CommandRenderer::refresh() {
  m_window->stream << term::manip::move{1, 1};
  m_window->stream << m_currentCommand;
  m_window->stream << term::manip::cursor{.show = true};
  m_window->stream << std::flush;
}

void CommandRenderer::reset() {
  m_currentCommand.clear();
  m_window->stream << term::manip::cursor{.show = false};
  m_window->stream << term::manip::clear{};
  m_window->stream << term::manip::move{1, 1};
  m_window->stream << std::flush;
}

void CommandRenderer::putChar(char c) {
  m_currentCommand.push_back(c);
  m_window->stream << term::manip::move{1, 1};
  m_window->stream << m_currentCommand;
  m_window->stream << term::manip::cursor{.show = true};
  m_window->stream << std::flush;
  //  m_window->stream << c.toLatin1(); // FIXME
}

void CommandRenderer::popBack() {
  m_currentCommand.pop_back();
  m_window->stream << term::manip::clear{};
  m_window->stream << term::manip::move{1, 1};
  m_window->stream << m_currentCommand;
  m_window->stream << term::manip::cursor{.show = !m_currentCommand.empty()};
  m_window->stream << std::flush;
}

#include "renderer/moc_command_renderer.cpp"
