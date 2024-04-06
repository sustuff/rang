#include <catch2/catch_all.hpp>

#include "keystroke_parser.hpp"

struct CallCounter {
    int getCallCountAndReset() {
      int tmp = callCount;
      callCount = 0;
      return tmp;
    }

    int callCount{};
};

TEST_CASE("keystroke test") {
  QKeyCombination escape(Qt::Key_Escape);
  Keystroke keystroke_escape{QKeyCombination(Qt::Key_Escape)};

  CallCounter counter1, counter2, counter3, counter4;
  auto action1 = std::function([&counter1]() { counter1.callCount += 1; });
  auto action2 = std::function([&counter2]() { counter2.callCount += 1; });
  auto action3 = std::function([&counter3]() { counter3.callCount += 1; });
  auto action4 = std::function([&counter4]() { counter4.callCount += 1; });

  auto getCallCountsAndReset = [&]() -> std::tuple<int, int, int, int> {
    return {counter1.getCallCountAndReset(), counter2.getCallCountAndReset(),
            counter3.getCallCountAndReset(), counter4.getCallCountAndReset()};
  };

  SECTION("trivial keystroke") {
    KeystrokeParser parser;
    parser.registerKeystroke(keystroke_escape, action1);
    REQUIRE(counter1.getCallCountAndReset() == 0);
    parser.nextKeyCombination(escape);
    REQUIRE(counter1.getCallCountAndReset() == 1);
  }

  QKeyCombination shift_a(Qt::ShiftModifier, Qt::Key_A);
  QKeyCombination ctrl_d(Qt::ControlModifier, Qt::Key_D);
  QKeyCombination e(Qt::Key_E);
  QKeyCombination a(Qt::Key_A);
  QKeyCombination d(Qt::Key_D);

  SECTION("non-trivial keystroke") {
    KeystrokeParser parser;
    parser.registerKeystroke({shift_a, d}, action1);
    parser.registerKeystroke({shift_a, ctrl_d}, action2);
    parser.registerKeystroke({d, ctrl_d}, action3);
    parser.registerKeystroke({d, d, a, d}, action4);

    parser.nextKeyCombination(shift_a);
    parser.nextKeyCombination(d);
    REQUIRE(getCallCountsAndReset() == std::tuple{1, 0, 0, 0});

    parser.nextKeyCombination(shift_a);
    parser.nextKeyCombination(e);  // nonexistent
    parser.nextKeyCombination(shift_a);
    parser.nextKeyCombination(ctrl_d);
    REQUIRE(getCallCountsAndReset() == std::tuple{0, 1, 0, 0});

    parser.nextKeyCombination(d);
    parser.nextKeyCombination(d);
    parser.nextKeyCombination(ctrl_d);  // should reset after this line
    REQUIRE(getCallCountsAndReset() == std::tuple{0, 0, 0, 0});
    parser.nextKeyCombination(d);
    parser.nextKeyCombination(ctrl_d);  // and here should be ok
    REQUIRE(getCallCountsAndReset() == std::tuple{0, 0, 1, 0});

    parser.nextKeyCombination(d);
    parser.nextKeyCombination(d);
    parser.nextKeyCombination(a);
    parser.nextKeyCombination(d);
    REQUIRE(getCallCountsAndReset() == std::tuple{0, 0, 0, 1});
  }
}
