#include "Solution.hpp"
#include "md5cpp.hpp"
#include <map>

static std::map<std::string, std::string> memoize;

std::string
key(const std::string& input, bool part2)
{
  decltype(memoize)::const_iterator it;
  if ((it = memoize.find(input)) != memoize.end())
    return it->second;
  std::string hash{MessageDigest5(input)};
  if (part2)
    for (int i{0}; i < 2016; ++i)
      hash.assign(MessageDigest5(hash));
  memoize.emplace(input, hash);
  return hash;
}

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  std::string in;
  std::getline(is, in);
  int val{-1}, i{0}, found{0};
  while (found != 64) {
    const std::string h1{key(in + std::to_string(++val), part2)};
    for (i = 0; i < 29; ++i) // match 3
      if (h1[i] == h1[i + 1] && h1[i] == h1[i + 2])
        break;
    if (i >= 29)
      continue;
    const char c{h1[i]};
    for (int off{1}; off <= 1000; ++off) {
      const std::string h2{key(in + std::to_string(val + off), part2)};
      for (i = 0; i < 27; ++i) // match 5
        if (c == h2[i] && c == h2[i + 1] && c == h2[i + 2] && c == h2[i + 3] && c == h2[i + 4])
          break;
      if (i < 27) {
        ++found;
        break;
      }
    }
  }
  memoize.clear();
  os << --val << std::endl;
}
