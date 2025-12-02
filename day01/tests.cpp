#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <fstream>
#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";
  std::istringstream in(data);

  Day01Result res = solve(in);

  CHECK(res.part1 == 3);
  CHECK(res.part2 == 6);
}

// TEST_CASE("example from sample1.txt") {
//   std::ifstream in("inputs/sample1.txt");
//   REQUIRE(!!in); // fail test if file is missing
//
//   Day01Result res = solve(in);
//
//  // Fill in when you know expected outputs for sample1.txt
//  // CHECK(res.part1 == ...);
//  // CHECK(res.part2 == ...);
// }
