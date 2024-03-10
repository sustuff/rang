#ifndef RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_
#define RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_

#include "buffer.hpp"

class FileListBuffer : public Buffer {
    Q_OBJECT
  public:
    QVector<QString> getLines() override;

  public slots:
    void update() override;
    void setPath(const std::filesystem::path& newPath);

  private:
    QDir dir;
    QFileInfoList fileList;
};

#endif  // RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_
