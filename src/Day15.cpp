#include "Solution.hpp"
#include <regex>
#include <x86intrin.h>

using uint32x8_t = unsigned int __attribute__((ext_vector_type(8)));

union vint {
  uint32x8_t v;
  uint32_t a[8];
};

const static std::regex PARSE{R"(Disc #\d+ has (\d+) positions; at time=0, it is at position (\d+).)"};

template <>
void
solve<Day15>(bool part2, std::istream& is, std::ostream& os)
{
  vint size = {1}, pos = {0}, time, c = {0};
  time.v = {0, 1, 2, 3, 4, 5, 6, 7};
  int count{0}, step{0};
  for (std::string line; std::getline(is, line); ++count) {
    std::smatch m;
    std::regex_match(line, m, PARSE);
    size.a[count] = std::stoi(m.str(1));
    pos.a[count] = std::stoi(m.str(2));
  }
  if (part2)
    size.a[count] = 11, pos.a[count] = 0, ++count;
  do {
    c.v = (pos.v + time.v + ++step) % size.v;
  } while (!_mm256_testz_si256(c.v, c.v));
  os << step << std::endl;
}
