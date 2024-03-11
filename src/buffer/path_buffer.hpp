#ifndef RANG_SRC_BUFFER_PATH_BUFFER_HPP_
#define RANG_SRC_BUFFER_PATH_BUFFER_HPP_

#include "buffer.hpp"

/// Most of buffers represent some 'path' in some form.
class PathBuffer : public Buffer {
    Q_OBJECT
  public:
    using Buffer::Buffer;

  public slots:
    void setPath(std::filesystem::path newPath);

  protected:
    std::filesystem::path m_path;
};

#endif  // RANG_SRC_BUFFER_PATH_BUFFER_HPP_
