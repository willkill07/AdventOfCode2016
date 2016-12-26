#include "Solution.hpp"
#include "assembunny.hpp"

template <>
void
solve<Day12>(bool part2, std::istream& is, std::ostream& os)
{
  os << Assembunny{is}.set('c', part2 ? 1 : 0).optAdd().optMul().run().get('a') << std::endl;
}
