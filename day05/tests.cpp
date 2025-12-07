#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(3-5
10-14
16-20
12-18

1
5
8
11
17
32)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 3);
  CHECK(res.part2 == 14);
}
