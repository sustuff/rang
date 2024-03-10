#ifndef RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_
#define RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_

#include "buffer.hpp"

class FileInfoBuffer : public Buffer {
    Q_OBJECT
  public:
    QVector<QString> getLines() override;

  public slots:
    void update() override;
    void setPath(std::filesystem::path new_path);

  private:
    QFileInfo fileInfo;
    std::filesystem::path path;
};

#endif  // RANG_SRC_BUFFER_FILE_INFO_BUFFER_HPP_
