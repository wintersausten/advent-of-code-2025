#include "solve.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

struct Range {
  long long start;
  long long end;
};

long long digits(long long n) { return std::to_string(n).size(); }

long long first_half(long long n) {
  std::string s = std::to_string(n);
  return std::stoll(s.substr(0, s.size() / 2));
}

long long second_half(long long n) {
  std::string s = std::to_string(n);
  return std::stoll(s.substr(s.size() / 2));
}

long long pow10(long long n) {
  long long x = 1;
  while (n--)
    x *= 10;
  return x;
}

long long repeat_number(long long n) {
  std::string s = std::to_string(n);
  return std::stoll(s + s);
}

Result solve(std::istream &in) {
  Result res{0, 0};
  std::vector<Range> ranges;

  std::string line, token;

  std::getline(in, line);
  std::stringstream ss(line);
  while (std::getline(ss, token, ',')) {
    int dash = token.find('-');
    long long a = std::stoll(token.substr(0, dash));
    long long b = std::stoll(token.substr(dash + 1));

    ranges.push_back({a, b});
  }

  for (const auto &r : ranges) {
    // find a range of even digit numbers to iterate through
    long long search_start = r.start;
    while (search_start <= r.end) {
      // get to the magnitude with viable results
      while (digits(search_start) % 2 != 0) {
        search_start = pow10(digits(search_start));
      }
      if (search_start > r.end) {
        break;
      }

      long long first_half_start = first_half(search_start);
      long long first_half_end = digits(search_start) == digits(r.end)
                                     ? first_half(r.end)
                                     : pow10(digits(search_start) / 2) - 1;
      for (long long i = first_half_start; i <= first_half_end; i++) {
        long long test_id = repeat_number(i);
        if (r.start <= test_id && test_id <= r.end) {
          res.part1 += test_id;
        }
      }

      search_start = pow10(digits(search_start) + 1);
    }
  }

  return res;
}
