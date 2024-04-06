#include "renderer/text_renderer.hpp"

TextRenderer::TextRenderer(Buffer* buffer) : Renderer{buffer}, buffer{buffer} {
  connect(buffer, &Buffer::contentChanged, this, &TextRenderer::update);
  update();
}

void TextRenderer::update() {
  for (const Line& line : buffer->getLines()) {
    for (const Word& word : line.getPrefix(80).getWords()) {
      qInfo() << word.getContent();
    }
  }
}

#include "renderer/moc_text_renderer.cpp"
