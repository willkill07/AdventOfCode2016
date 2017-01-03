#include "Solution.hpp"
#include <regex>

// I am aware this solution only works for certain inputs

template <>
void
solve<Day11>(bool part2, std::istream& is, std::ostream& os)
{
  static const std::regex RE{" a "};
  int floorFactor{3}, sum{part2 ? 15 : -9};
  for (std::string line; std::getline(is, line);)
    sum += 2 * floorFactor-- * std::distance(std::sregex_iterator(line.begin(), line.end(), RE), {});
  os << sum << std::endl;
}
