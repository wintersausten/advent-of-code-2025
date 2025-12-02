#include "solve.hpp"

#include <iostream>
#include <sstream>
#include <string>

constexpr int DIAL_SIZE = 100;

int wrap(int x, int n) { return ((x % n) + n) % n; }

int count_hits_right(int pos, int n) { return (pos + n) / DIAL_SIZE; }

int count_hits_left(int pos, int n) {
  int tmp = pos - n;
  int hits = 0;
  if (pos != 0 && tmp <= 0) {
    hits += 1;
  }
  hits += (-tmp) / DIAL_SIZE;
  return hits;
}

Day01Result solve(std::istream &in) {
  Day01Result res{0, 0};

  std::string line;

  int pos{50};

  while (std::getline(in, line)) {
    std::istringstream ss(line);
    char c;
    int n;
    ss >> c >> n;

    if (c == 'L') {
      res.part2 += count_hits_left(pos, n);
      pos = wrap(pos - n, DIAL_SIZE);
    } else {
      res.part2 += count_hits_right(pos, n);
      pos = wrap(pos + n, DIAL_SIZE);
    }

    if (pos == 0) {
      res.part1 += 1;
    }
  }

  return res;
}
