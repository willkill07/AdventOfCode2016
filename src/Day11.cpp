#include "Solution.hpp"
#include "io.hpp"

// I am aware this solution only works for certain inputs
const static std::regex ITEM{R"(a (\w+)(?:-compatible (microchip)| (generator)))"};

template <>
void
solve<Day11>(bool part2, std::istream& is, std::ostream& os)
{
  int floorFactor{3}, sum{part2 ? 15 : -9};
  for (auto line : io::by<io::line>(is))
    sum += 2 * floorFactor-- * std::distance(std::sregex_iterator(line.begin(), line.end(), ITEM), {});
  os << sum << std::endl;
}
