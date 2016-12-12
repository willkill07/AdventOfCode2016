#ifndef _WILLIAM_KILLIAN_UTIL_HPP_
#define _WILLIAM_KILLIAN_UTIL_HPP_

#include <algorithm>
#include <string>
#include <vector>

namespace util {

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

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;
  while((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if(start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}

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
