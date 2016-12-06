#include "Solution.hpp"
#include <array>

template <>
void
solve<Day06>(bool part2, std::istream &is, std::ostream &os)
{
  std::array<std::array<int, 26>, 8> counts;
  std::string line;
  while (std::getline(is, line))
    for (uint i{0}; i < line.size(); ++i)
      ++counts[i][line[i] - 'a'];
  auto cmp{part2 ? std::min_element<const int *> : std::max_element<const int *>};
  for (const auto &c : counts)
    os << char(cmp(c.begin(), c.end()) - c.begin() + 'a');
  os << std::endl;
}
