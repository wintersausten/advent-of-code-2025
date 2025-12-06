#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 13);
  CHECK(res.part2 == 43);
}
