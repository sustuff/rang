#ifndef RANG_SRC_WINDOW_TERMINAL_RENDERER_HPP_
#define RANG_SRC_WINDOW_TERMINAL_RENDERER_HPP_

#include "renderer.hpp"

class TerminalRenderer : public Renderer {
    Q_OBJECT
  public:
    using Renderer::Renderer;
};

#endif  // RANG_SRC_WINDOW_TERMINAL_RENDERER_HPP_
