#ifndef RANG_SRC_BUFFER_TEXT_FILE_PREVIEW_BUFFER_HPP_
#define RANG_SRC_BUFFER_TEXT_FILE_PREVIEW_BUFFER_HPP_

#include "path_buffer.hpp"

class TextFilePreviewBuffer : public PathBuffer {
    Q_OBJECT
  public:
    using PathBuffer::PathBuffer;

  public slots:
    void update() override;
    QVector<QString> getLines() override;

  private:
    QString fileContent;
};

#endif  // RANG_SRC_BUFFER_TEXT_FILE_PREVIEW_BUFFER_HPP_
