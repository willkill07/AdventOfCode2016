#include "Solution.hpp"
#include <cmath>

template <>
void
solve<Day19>(bool part2, std::istream& is, std::ostream& os)
{
  int elves{*std::istream_iterator<int>(is)};
  int r{part2 ? int(std::pow(3, int((std::log2(elves - 1) / std::log2(3))))) :  __builtin_clz(elves)};
  os << (part2 ? elves - r + std::max(elves - 2 * r, 0) : elves << (r + 1) >> r | 1) << std::endl;
}
