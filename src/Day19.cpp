#include "Solution.hpp"

template <>
void
solve<Day19>(bool part2, std::istream& is, std::ostream& os)
{
  int elfCount{std::stoi(std::string{std::istream_iterator<char>(is), {}})};
  int result{part2 ? 1 : __builtin_clz(elfCount)};
  if (part2) {
    while ((result * 3) <= elfCount)
      result *= 3;
    result = elfCount - result;
  } else
    result = (elfCount << (result + 1) >> result | 1);
  os << result << std::endl;
}
