// module or class includes
#include <QtCore>

// text stream is text-codec aware
QTextStream cout(stdout, QIODevice::WriteOnly);

int main() {
  cout << "Hello, world!" << Qt::endl;
}
