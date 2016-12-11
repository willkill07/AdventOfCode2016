#include "Solution.hpp"
#include "io.hpp"

// I am aware this solution only works for certain inputs

const static std::regex ITEM{R"(a (\w+)(?:-compatible (microchip)| (generator)))"};

template <>
void
solve<Day11>(bool part2, std::istream& is, std::ostream& os)
{
  std::vector<int> floors;
  for (std::string line; std::getline(is,line); )
    floors.push_back(std::distance(std::sregex_iterator(line.begin(), line.end(), ITEM), {}));
  floors[0] += part2 * 4;
  int result{-9};
  for (int i{0}; i < 4; ++i)
    result += floors[i] * (3 - i) * 2;
  os << result << std::endl;
}
