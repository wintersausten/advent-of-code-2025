#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  )";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 4277556);
  CHECK(res.part2 == 3263827);
}
