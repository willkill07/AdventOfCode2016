#include "Solution.hpp"

size_t
dragon_parity(size_t n)
{
  size_t gray{n ^ (n >> 1)};
  return (gray ^ __builtin_popcountl(n & gray)) & 1;
}

size_t
parity(const std::string& input)
{
  auto   in{input.data()};
  size_t input_parity{0};
  for (size_t i{0}, j = input.size() * 2; i < j; ++in, ++i, --j)
    input_parity ^= (static_cast<size_t>(*in & 1) << (i + 1)) ^ (static_cast<size_t>((*in & 1) ^ 1) << j);
  for (size_t i{1}; i < 64; i <<= 1)
    input_parity ^= input_parity << i;
  return input_parity;
}

std::string
dragon(const std::string& input, size_t disk_size)
{
  std::string out;
  const size_t LEN{input.size()}, INCR{disk_size & -disk_size};
  size_t par{parity(input)}, prev{0};
  for (size_t length{INCR}; length <= disk_size; length += INCR) {
    size_t dragons{length / (LEN + 1)},
    p{1 & (dragon_parity(dragons) ^ (((length - dragons) / (LEN << 1)) & LEN) ^ (par >> ((length - dragons) % (LEN << 1))))};
    out.push_back("10"[p ^ prev]);
    prev = p;
  }
  return out;
}

template <>
void
solve<Day16>(bool part2, std::istream& is, std::ostream& os)
{
  const size_t LIM{part2 ? 35651584U : 272U};
  std::string in;
  is >> in;
  os << dragon(in, LIM) << std::endl;
}
