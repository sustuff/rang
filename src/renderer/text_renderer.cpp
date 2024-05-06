#include "renderer/text_renderer.hpp"
#include <iostream>
#include "term/manip.hpp"

TextRenderer::TextRenderer(Buffer* buffer, std::unique_ptr<term::window> window, QObject* parent)
    : Renderer(std::move(window), parent), buffer{buffer} {
  connect(buffer, &Buffer::contentChanged, this, &TextRenderer::update);
  update();
}

void TextRenderer::update() {
  m_window->stream << term::manip::clear{};
  int y = 0;
  for (const Line& line : buffer->getLines()) {
    if (++y > m_window->stream.dimensions.size_y) {
      break;
    }
    m_window->stream << term::manip::move{1, y};
    for (const Word& word : line.getPrefix(m_window->stream.dimensions.size_x)) {
      m_window->stream << word.print();
    }
  }
  m_window->stream << std::flush;
}

void TextRenderer::refresh() {
  update();
}


#include "renderer/moc_text_renderer.cpp"
