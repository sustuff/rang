#ifndef RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_
#define RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_

#include <optional>
#include "path_buffer.hpp"

class FileListBuffer : public PathBuffer {
    Q_OBJECT
  public:
    using PathBuffer::PathBuffer;

    QVector<Line> getLines() override;
    std::optional<std::filesystem::path> getCurrentFile() const;

  signals:
    void currentFileChanged(std::optional<std::filesystem::path>);

  public slots:
    void update() override;
    void goDown();
    void goUp();

  private:
    QFileInfoList fileList;
    quint32 currentFile = 0;

    void sendUpdates();
};

#endif  // RANG_SRC_BUFFER_FILE_LIST_BUFFER_HPP_
