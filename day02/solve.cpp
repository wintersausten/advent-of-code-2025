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

long long solve2(std::istream &in) {
  long long result{0};
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
    for (long long i = r.start; i <= r.end; i++) {
      std::string s = std::to_string(i);
      int n = static_cast<int>(s.size());
      for (int set_size = 1; set_size <= n / 2; set_size++) {
        if (n % set_size != 0)
          continue;
        std::string set = s.substr(0, set_size);
        bool is_repeating = true;
        for (int j = set_size; j <= n - set_size; j += set_size) {
          if (s.substr(j, set_size) != set) {
            is_repeating = false;
            break;
          }
        }
        if (is_repeating) {
          result += i;
          break;
        }
      }
    }
  }

  return result;
}

long long solve1(std::istream &in) {
  long long result{0};
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
          result += test_id;
        }
      }

      search_start = pow10(digits(search_start) + 1);
    }
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
