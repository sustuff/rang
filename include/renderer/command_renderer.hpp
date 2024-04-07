#ifndef RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_
#define RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_

#include "renderer/renderer.hpp"
#include "term/window.hpp"

class CommandRenderer : public Renderer {
    Q_OBJECT
  private:
    std::string m_currentCommand;
    std::shared_ptr<term::window> m_window;

  public:
    explicit CommandRenderer(std::shared_ptr<term::window> window);

  public slots:
    void putChar(char c);
    void popBack();
    void reset();
};

#endif  // RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_
