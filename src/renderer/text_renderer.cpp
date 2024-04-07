#include "renderer/text_renderer.hpp"
#include <iostream>

TextRenderer::TextRenderer(Buffer* buffer) : Renderer{buffer}, buffer{buffer} {
  connect(buffer, &Buffer::contentChanged, this, &TextRenderer::update);
  update();
}

void TextRenderer::update() {
  std::cout << term::modifiers::clear << std::flush;
  int y = 0;
  for (const Line& line : buffer->getLines()) {
    for (const Word& word : line.getPrefix(80).getWords()) {
      std::cout << word.print(y);
    }
    std::cout << std::endl;
    ++y;
  }
}

#include "renderer/moc_text_renderer.cpp"
