#ifndef _WILLIAM_KILLIAN_UTIL_HPP_
#define _WILLIAM_KILLIAN_UTIL_HPP_

#include <algorithm>
#include <string>
#include <vector>

namespace util {

int fast_itoa(int, char*);

class combination {
  bool              cont{true};
  std::vector<bool> v;

  public:
  combination(size_t n, size_t r)
    : v(r, true)
  {
    v.resize(n, false);
  }

  bool
  next(std::vector<size_t>& res)
  {
    if (!cont)
      return false;
    for (size_t i{0}, j{0}; i < v.size(); ++i)
      if (v[i])
        res[j++] = i;
    cont = std::prev_permutation(std::begin(v), std::end(v));
    return true;
  }
};

std::vector<std::string>
split(const std::string& text, const std::string& delims);

constexpr uint64_t
hash(const char* str, uint64_t ret = 0xCBF29CE484222325ull)
{
  return (*str) ? ret : hash(str + 1, (ret ^ *(str + 1)) * 0x100000001B3ull);
}

constexpr uint64_t
hash(const std::string& str)
{
  return hash(str.c_str());
}
}

constexpr uint64_t operator"" _hash(const char* p, size_t)
{
  return util::hash(p);
}

#endif
