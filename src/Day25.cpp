#include "Solution.hpp"
#include "assembunny.hpp"

static const std::string ZERO_ONE{"010101010101"};

template <>
void
solve<Day25>(bool part2, std::istream& is, std::ostream& os)
{
  if (part2) {
    os << "Happy Advent of Code 2016!" << std::endl;
    return;
  }
  Assembunny asmb{is};
  asmb.optAdd().optRemoveInfiniteLoops().setOutputBufferLimit(12);
  for (int a{0}; a < 256; ++a)
    if (asmb.clearOutputBuffer().set('a', a).run().getOuputBuffer() == ZERO_ONE) {
      os << a << std::endl;
      return;
    }
}
