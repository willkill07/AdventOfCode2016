#include "Solution.hpp"
#include "assembunny.hpp"
#include <regex>

template <>
void
solve<Day25>(bool part2, std::istream& is, std::ostream& os)
{
  if (part2) {
    os << "Happy Advent of Code 2016!" << std::endl;
    return;
  }
  static const std::regex ZERO_ONE{R"((01)+$)"};
  Assembunny asmb{is};
  asmb.optAdd().setOutputBufferLimit(12);
  for (int a{0}; a < 256; ++a)
    if (std::regex_match(asmb.clearOutputBuffer().set('a', a).run().getOuputBuffer(), ZERO_ONE) && os << a << std::endl)
      return;
}
