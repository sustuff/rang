#ifndef RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_
#define RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_

#include "path_buffer.hpp"

class FileInfoBuffer : public PathBuffer {
    Q_OBJECT
  public:
    using PathBuffer::PathBuffer;

    QVector<QString> getLines() override;

  public slots:
    void update() override;

  private:
    QFileInfo fileInfo;
};

#endif  // RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_
