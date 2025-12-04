#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"

#include "solve.hpp"

#include <fstream>
#include <sstream>

TEST_CASE("example from problem statement") {
  std::string data =
      R"(11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 1227775554);
  CHECK(res.part2 == 4174379265);
}

TEST_CASE("1") {
  std::string data = R"(11-22)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 33);
}
TEST_CASE("2") {
  std::string data = R"(95-115)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 99);
  CHECK(res.part2 == 210);
}
TEST_CASE("3") {
  std::string data = R"(998-1012)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 1010);
}
TEST_CASE("4") {
  std::string data = R"(1188511880-1188511890)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 1188511885);
}
TEST_CASE("5") {
  std::string data = R"(222220-222224)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 222222);
}
TEST_CASE("6") {
  std::string data = R"(1698522-1698528)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 0);
}
TEST_CASE("7") {
  std::string data = R"(446443-446449)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 446446);
}
TEST_CASE("8") {
  std::string data = R"(38593856-38593862)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 38593859);
}
TEST_CASE("9") {
  std::string data = R"(1-19)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 11);
}
TEST_CASE("10") {
  std::string data = R"(26-45)";
  std::istringstream in(data);

  Result res = solve(in);

  CHECK(res.part1 == 77);
}
