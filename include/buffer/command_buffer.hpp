#ifndef RANG_INCLUDE_BUFFER_COMMAND_BUFFER_HPP_
#define RANG_INCLUDE_BUFFER_COMMAND_BUFFER_HPP_

#include "buffer/buffer.hpp"

class CommandBuffer : public Buffer {
    Q_OBJECT
  public:
    using Buffer::Buffer;

    Q_PROPERTY(QString input READ input WRITE setInput NOTIFY contentChanged);

    const QString& input();
    void setInput(const QString& string);
    QVector<Line> getLines() override;

  public slots:
    void update() override;

  signals:
    void contentChanged();

  private:
    QString m_input;
};

#endif  // RANG_INCLUDE_BUFFER_COMMAND_BUFFER_HPP_
