#include <catch2/catch_all.hpp>

#include <fstream>
#include <iostream>

#include "buffer/file_info_buffer.hpp"
#include "buffer/file_list_buffer.hpp"
#include "buffer/text_file_preview_buffer.hpp"

char getRandomChar() {
  return QRandomGenerator::global()->bounded('a', 'z' + 1);
}

std::string getRandomString(std::size_t size) {
  std::string randomString;
  std::generate_n(std::back_inserter(randomString), size, getRandomChar);
  return randomString;
}

TEST_CASE("buffer test") {
  using namespace std::filesystem;

  const path tmpDir{temp_directory_path() / ("buffer_test_" + getRandomString(8))};
  const path textFile1{tmpDir / "B" / "..f-f . f."};
  const path textFile2{tmpDir / ".D" / "file2"};
  create_directory(tmpDir);
  create_directory(tmpDir / "B");
  std::ofstream{textFile1} << "Hello Sailor!\n";
  std::ofstream{tmpDir / "file"};
  std::ofstream{tmpDir / "B" / "file"};
  create_directory(tmpDir / ".D");
  std::ofstream{tmpDir / ".D" / "file1"};
  std::ofstream{textFile2} << "\nfile\n\n2\n";
  std::ofstream{tmpDir / ".D" / "file3"};
  create_directory(tmpDir / "A ");
  create_directory(tmpDir / " A");
  create_directory(tmpDir / " A" / "A ");
  create_directory(tmpDir / "A " / " A");
  std::ofstream{tmpDir / "A " / " A" / "file"};
  std::ofstream{tmpDir / "A " / " file"};
  std::ofstream{tmpDir / "A " / "file"};

  recursive_directory_iterator dirIter{tmpDir};
  std::vector<directory_entry> files{begin(dirIter), end(dirIter)};
  files.emplace_back(tmpDir);

  SECTION("FileInfoBuffer") {
    FileInfoBuffer buffer;
    for (const directory_entry& dirEntry : files) {
      buffer.setPath(dirEntry.path());
      auto lines = buffer.getLines();
      REQUIRE(lines.size() == 3);
      REQUIRE(lines[0] == dirEntry.path().c_str());
    }
  }

  SECTION("TextFilePreviewBuffer") {
    TextFilePreviewBuffer buffer;
    buffer.setPath(textFile1);
    REQUIRE(buffer.getLines() == QVector<Line>{"Hello Sailor!", ""});
    buffer.setPath(textFile2);
    REQUIRE(buffer.getLines() == QVector<Line>{"", "file", "", "2", ""});
  }

  SECTION("FileListBuffer") {
    FileListBuffer buffer;
    for (const directory_entry& dirEntry : files) {
      if (!dirEntry.is_directory()) {
        continue;
      }

      QVector<Line> localFiles;
      for (const directory_entry& localDirEntry : directory_iterator{dirEntry.path()}) {
        QString filename{localDirEntry.path().filename().c_str()};
        if (filename[0] != '.') {
          localFiles.push_back(localDirEntry.path().filename().c_str());
        }
      }
      std::sort(localFiles.begin(), localFiles.end());

      buffer.setPath(dirEntry.path());
      REQUIRE(buffer.getLines() == localFiles);
    }
  }

  remove_all(tmpDir);
}
