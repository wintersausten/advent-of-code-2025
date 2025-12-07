#include "solve.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string which = (argc > 1) ? argv[1] : "input";

  std::string path = "inputs/" + which + ".txt";

  std::ifstream in(path);
  if (!in) {
    std::cerr << "Failed to open " << path << "\n";
    return 1;
  }

  Result res = solve(in);

  std::cout << "Part 1: " << res.part1 << "\n";
  std::cout << "Part 2: " << res.part2 << "\n";

  return 0;
}
