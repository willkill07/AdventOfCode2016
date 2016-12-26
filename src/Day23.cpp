#include "Solution.hpp"
#include "assembunny.hpp"

template <>
void
solve<Day23>(bool part2, std::istream& is, std::ostream& os)
{
  os << Assembunny{is}.set('a', part2 ? 12 : 7).optMul().optAdd().run().get('a') << std::endl;
}
