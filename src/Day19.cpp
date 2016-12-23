#include "Solution.hpp"
#include <cmath>

template <>
void
solve<Day19>(bool part2, std::istream& is, std::ostream& os)
{
  const int ELVES{*std::istream_iterator<int>(is)};
  const int RESULT{part2 ? int(std::pow(3, int((std::log2(ELVES - 1) / std::log2(3))))) :  __builtin_clz(ELVES)};
  os << (part2 ? ELVES - RESULT + std::max(ELVES - 2 * RESULT, 0) : ELVES << (RESULT + 1) >> RESULT | 1) << std::endl;
}
