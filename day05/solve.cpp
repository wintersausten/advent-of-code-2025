#include "solve.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>

struct Range {
  long long start;
  long long end;
};

int solve1(std::istream &in) {
  int result{0};
  std::string line;

  std::vector<Range> fresh_range_list;
  while (std::getline(in, line)) {
    if (line.empty())
      break;

    auto pos = line.find("-");
    long long start = std::stoll(line.substr(0, pos));
    long long end = std::stoll(line.substr(pos + 1));
    fresh_range_list.push_back({start, end});
  }

  std::vector<long long> ingredient_list;
  while (std::getline(in, line)) {
    ingredient_list.push_back(std::stoll(line));
  }

  for (long long ingredient : ingredient_list) {
    for (Range fresh_range : fresh_range_list) {
      if (fresh_range.start <= ingredient && ingredient <= fresh_range.end) {
        result++;
        break;
      }
    }
  }

  return result;
}

long long solve2(std::istream &in) {
  std::string line;
  long long result{0};

  std::vector<Range> fresh_range_list;
  while (std::getline(in, line)) {
    if (line.empty())
      break;

    auto pos = line.find("-");
    long long start = std::stoll(line.substr(0, pos));
    long long end = std::stoll(line.substr(pos + 1));
    fresh_range_list.push_back({start, end});
  }

  std::ranges::sort(fresh_range_list, {}, &Range::start);
  std::vector<Range> combined_range_list{fresh_range_list[0]};
  for (auto &fresh_range : fresh_range_list | std::views::drop(1)) {
    if (fresh_range.start <= combined_range_list.back().end) {
      combined_range_list.back().end =
          std::max(combined_range_list.back().end, fresh_range.end);
    } else {
      combined_range_list.push_back(fresh_range);
    }
  }

  for (auto &fresh_range : combined_range_list) {
    result += fresh_range.end - fresh_range.start + 1;
  }

  return result;
}

/* had to try the dumb way first after getting got for not taking the simple
 * route before, now on to merge intervals
 */
// long long solve2(std::istream &in) {
//   std::string line;
//
//   std::vector<Range> fresh_range_list;
//   while (std::getline(in, line)) {
//     if (line.empty())
//       break;
//
//     auto pos = line.find("-");
//     long long start = std::stoll(line.substr(0, pos));
//     long long end = std::stoll(line.substr(pos + 1));
//     fresh_range_list.push_back({start, end});
//   }
//
//   std::unordered_set<long long> seen;
//   for (Range fresh_range : fresh_range_list) {
//     for (long long i = fresh_range.start; i <= fresh_range.end; i++) {
//       seen.insert(i);
//     }
//   }
//
//   return seen.size();
// }

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  in.clear();
  in.seekg(0);
  res.part2 = solve2(in);
  return res;
}
