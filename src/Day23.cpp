#include "Solution.hpp"
#include "assembunny.hpp"

template <>
void
solve<Day23>(bool part2, std::istream& is, std::ostream& os)
{
  Assembunny ab{is};
  ab.set('a', part2 ? 12 : 7).set('b', 0).set('c', 0).set('d', 0);
  ab.optMul().optAdd().run();
  os << ab.get('a') << std::endl;
}
