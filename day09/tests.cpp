#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 50);
}
