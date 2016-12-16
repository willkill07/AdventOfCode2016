#include "Solution.hpp"
#include <string>

template <>
void
solve<Day16>(bool part2, std::istream& is, std::ostream& os)
{
  uint LIM{part2 ? 35651584U : 272U};
  std::string in;
  is >> in;
  in.reserve(LIM << 1); // big buffer
  while (in.size() < LIM) {
    in.push_back('0');
    auto b = in.rbegin();
    while (++b != in.rend())
      in.push_back(*b ^ 1);
  }
  in.resize(LIM);
  while (!(in.size() & 1)) {
    auto w = in.begin();
    for (auto r = in.cbegin(); r != in.cend(); r += 2)
      *w++ = '0' + (*r == *(r + 1));
    in.resize(in.size() >> 1);
  }
  os << in << std::endl;
}
