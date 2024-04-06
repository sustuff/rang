#include "renderer/text_renderer.hpp"
#include <iostream>
#include "termcolor.hpp"

TextRenderer::TextRenderer(Buffer* buffer) : Renderer{buffer}, buffer{buffer} {
  connect(buffer, &Buffer::contentChanged, this, &TextRenderer::update);
  update();
}

void TextRenderer::update() {
  for (const Line& line : buffer->getLines()) {
    for (const Word& word : line.getPrefix(80).getWords()) {
      std::cout << word;
    }
    std::cout << termcolor::reset << std::endl;
  }
}

#include "renderer/moc_text_renderer.cpp"
