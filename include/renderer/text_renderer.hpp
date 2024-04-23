#ifndef RANG_SRC_RENDERER_TEXT_RENDERER_HPP_
#define RANG_SRC_RENDERER_TEXT_RENDERER_HPP_

#include "buffer/buffer.hpp"
#include "renderer.hpp"
#include "term/window.hpp"

class TextRenderer : public Renderer {
    Q_OBJECT
  private:
    Buffer* buffer;
    std::shared_ptr<term::window> window;

  public:
    TextRenderer(Buffer* buffer, std::shared_ptr<term::window> window);

  public slots:
    void update();
};

#endif  // RANG_SRC_RENDERER_TEXT_RENDERER_HPP_
