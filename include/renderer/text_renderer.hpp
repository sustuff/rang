#ifndef RANG_SRC_RENDERER_TEXT_RENDERER_HPP_
#define RANG_SRC_RENDERER_TEXT_RENDERER_HPP_

#include "buffer/buffer.hpp"
#include "renderer.hpp"

class TextRenderer : public Renderer {
    Q_OBJECT
  private:
    Buffer* buffer;

  public:
    TextRenderer(Buffer* buffer, std::unique_ptr<term::window> window, QObject* parent = nullptr);

    void refresh() override;

  public slots:
    void update();
};

#endif  // RANG_SRC_RENDERER_TEXT_RENDERER_HPP_
