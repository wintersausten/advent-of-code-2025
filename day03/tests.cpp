#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(987654321111111
811111111111119
234234234234278
818181911112111)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 357);
  CHECK(res.part2 == 3121910778619);
}

TEST_CASE("subpart 1") {
  std::string data = R"(987654321111111)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 98);
  CHECK(res.part2 == 987654321111);
}

TEST_CASE("subpart 2") {
  std::string data = R"(234234234234278)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 78);
  CHECK(res.part2 == 434234234278);
}
