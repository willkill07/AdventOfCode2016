#include "Solution.hpp"
#include "assembunny.hpp"

template <>
void
solve<Day12>(bool part2, std::istream& is, std::ostream& os)
{
  Assembunny ab{is};
  ab.set('a', 0).set('b', 0).set('c', part2 ? 1 : 0).set('d', 0);
  ab.optAdd().optMul().run();
  os << ab.get('a') << std::endl;
}
