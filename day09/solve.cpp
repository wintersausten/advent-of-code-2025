#include "solve.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Coord {
  long long x;
  long long y;
};

long long square_size(Coord &a, Coord &b) {
  return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);
}

long long solve1(std::istream &in) {
  std::vector<Coord> coords;
  std::string line;
  long long x, y;
  char _;
  while (std::getline(in, line)) {
    std::stringstream ss(line);
    ss >> x >> _ >> y;
    coords.push_back({x, y});
  }

  long long max{};
  int n{static_cast<int>(coords.size())};
  for (int i = 0; i < n - 1; i++) {
    for (int j = i; j < n; j++) {
      long long size = square_size(coords[i], coords[j]);
      if (size > max)
        max = size;
    }
  }

  return max;
}

// long long solve2(std::istream &in) {
//   std::string line;
//   long long result{0};
//   return result;
// }

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  // in.clear();
  // in.seekg(0);
  // res.part2 = solve2(in);
  return res;
}
