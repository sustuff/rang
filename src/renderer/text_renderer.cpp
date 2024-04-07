#include "renderer/text_renderer.hpp"
#include <iostream>
#include "term/manip.hpp"

TextRenderer::TextRenderer(Buffer* buffer, std::shared_ptr<term::window> window)
    : Renderer{buffer}, buffer{buffer}, window{window} {
  connect(buffer, &Buffer::contentChanged, this, &TextRenderer::update);
  update();
}

void TextRenderer::update() {
  window->stream << term::manip::clear{};
  int y = 0;
  for (const Line& line : buffer->getLines()) {
    window->stream << term::manip::move{1, ++y};
    for (const Word& word : line.getPrefix(80).getWords()) {
      window->stream << word.print();
    }
  }
  window->stream << std::flush;
}

#include "renderer/moc_text_renderer.cpp"
