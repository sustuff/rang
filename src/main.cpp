#include <QtCore>

#include "app_info.hpp"
#include "client_main.hpp"
#include "meta.hpp"
#include "normal_main.hpp"

int main(int argc, char* argv[]) {
  register_qt_metatypes();

  if (argc > 0 && QFileInfo(argv[0]).fileName() == AppInfo::clientAppName) {
    return clientMain(argc, argv);
  } else {
    return normalMain(argc, argv);
  }
}
