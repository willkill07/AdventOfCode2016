#include "Solution.hpp"
#include <regex>
#include <x86intrin.h>

template <typename T, size_t N>
using vector = T __attribute__((ext_vector_type(N)));

template <typename T, size_t N>
union vec {
  vector<T,N> v; T a[N];
};

const static std::regex PARSE{R"(Disc #\d+ has (\d+) positions; at time=0, it is at position (\d+).)"};

template <>
void
solve<Day15>(bool part2, std::istream& is, std::ostream& os)
{
  vec<uint,8> size = {1}, pos = {0};
  int count{0}, step{0};
  for (std::string line; std::getline(is, line); ++count) {
    std::smatch m;
    std::regex_match(line, m, PARSE);
    size.a[count] = std::stoi(m.str(1));
    pos.a[count] = (std::stoi(m.str(2)) + count) % size.a[count];
  }
  if (part2)
    size.a[count] = 11, pos.a[count] = count, ++count;
  for ( ; !_mm256_testz_si256(pos.v, pos.v); ++step)
    pos.v += 1, pos.v += (pos.v >= size.v) * size.v;
  os << step << std::endl;
}
