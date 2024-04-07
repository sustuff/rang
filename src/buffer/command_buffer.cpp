#include "buffer/command_buffer.hpp"

#include <QtLogging>

void CommandBuffer::update() {
  emit contentChanged();
}

QVector<Line> CommandBuffer::getLines() {
  qInfo() << "GET LINES CALLED";
  return {Line(m_input)};
}

const QString& CommandBuffer::input() {
  return m_input;
}

void CommandBuffer::setInput(const QString& string) {
  m_input = string;
  emit contentChanged();
}

#include "buffer/moc_command_buffer.cpp"
