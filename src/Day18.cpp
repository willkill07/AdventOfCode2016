#include "Solution.hpp"

inline uint8_t
popcnt128(__int128 val)
{
  return __builtin_popcountl(static_cast<uint64_t>(val >> 64)) + __builtin_popcountl(static_cast<uint64_t>(val));
}

template <>
void
solve<Day18>(bool part2, std::istream& is, std::ostream& os)
{
  __int128 input{0}, mask{0};
  for (char c; is >> c;)
    input = (input << 1) | (c == '^'), mask = (mask << 1) | 1;
  uint64_t count{popcnt128(input)}, limit{part2 ? 400000U : 40U};
  for (uint64_t itr{1}; itr < limit; ++itr)
    count += popcnt128(input = ((input >> 1) ^ (input << 1)) & mask);
  os << ((limit * popcnt128(mask)) - count) << std::endl;
}
