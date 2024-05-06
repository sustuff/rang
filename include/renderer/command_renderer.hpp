#ifndef RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_
#define RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_

#include "renderer/renderer.hpp"

class CommandRenderer : public Renderer {
    Q_OBJECT
  private:
    std::string m_currentCommand;

  public:
    explicit CommandRenderer(std::unique_ptr<term::window> window, QObject* parent = nullptr);
    void refresh() override;

  public slots:
    void putChar(char c);
    void popBack();
    void reset();
};

#endif  // RANG_INCLUDE_RENDERER_COMMAND_RENDERER_HPP_
