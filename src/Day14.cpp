#include "Solution.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>
#include <map>
#include <regex>
#include <vector>

static std::map<std::string, std::string> memoize;

void key(const char* input, size_t len, bool part2, md5str_t* digest)
{
  md5str((uint8_t*)input, len, digest);
  if (part2)
    for (int i{0}; i < 2016; ++i)
      md5str((uint8_t*)digest, 32, digest);
}

const uint       GOAL{64}, WINDOW{1000};
const std::regex R3{R"((.)\1\1)", std::regex::optimize};
const std::regex R5{R"((.)\1\1\1\1)", std::regex::optimize};

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  md5str_t buf;
  std::vector<int> ind;
  std::map<char, std::vector<int>> threes;
  std::string in;
  is >> in;
  uint length(in.size()), end{UINT_MAX};
  in.resize(length + 10);
  for (uint val{0}; val < end; ++val) {
    key(in.data(), length + util::fast_itoa (val, &in[length]), part2, &buf);
    const std::string h{&buf.c[0], &buf.c[32]};
    for (std::sregex_iterator ri{h.begin(), h.end(), R5}, re{}; ri != re; ++ri) {
      char c{ri->str(1)[0]};
      for (auto i : threes[c])
        if (val - i <= WINDOW)
          if (ind.emplace_back(i), ind.size() == GOAL)
            end = i + WINDOW;
      threes[c].clear();
    }
    std::smatch m;
    if (std::regex_search(h, m, R3)) {
      char c{m.str(1)[0]};
      threes[c].emplace_back(val);
    }
  }
  std::sort(ind.begin(), ind.end());
  os << ind[GOAL - 1] << std::endl;
}
