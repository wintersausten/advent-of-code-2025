#include "solve.hpp"

#include <algorithm>
#include <iostream>
#include <string>

int solve1(std::istream &in) {
  int result{0};
  std::string line;
  std::vector<int> digits;

  while (std::getline(in, line)) {
    digits.clear();

    for (char c : line) {
      digits.push_back(c - '0');
    }

    int joltage{0}, n{static_cast<int>(digits.size())};
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        joltage = std::max(joltage, digits[i] * 10 + digits[j]);
      }
    }

    result += joltage;
  }

  return result;
}

int find_next_digit(int start, int rem, std::vector<int> digits) {
  int max_val{0};
  int max_i{start};

  int n{static_cast<int>(digits.size())};
  for (int i = start; i < n - rem; i++) {
    if (digits[i] == 9) {
      return i;
    }

    if (digits[i] > max_val) {
      max_val = digits[i];
      max_i = i;
    }
  }
  return max_i;
}

long long pow10(long long n) {
  long long x = 1;
  while (n--)
    x *= 10;
  return x;
}

long long solve2(std::istream &in) {
  long long result{0};
  std::string line;
  std::vector<int> digits;

  while (std::getline(in, line)) {
    digits.clear();

    for (char c : line) {
      digits.push_back(c - '0');
    }

    long long joltage{0};
    int i{0};
    for (int rem = 11; rem >= 0; rem--) {
      i = find_next_digit(i, rem, digits);
      joltage += digits[i] * pow10(rem);
      i += 1;
    }
    result += joltage;
  }

  return result;
}

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  in.clear();
  in.seekg(0);
  res.part2 = solve2(in);
  return res;
}

// going from left to right, can assume first 9 or largest number before last n
// is best option
