#include "Solution.hpp"
#include "md5.hpp"
#include <algorithm>
#include <map>
#include <regex>
#include <vector>

static std::map<std::string, std::string> memoize;

std::string
key(const char* input, size_t len, bool part2, md5str_t* digest)
{
  md5str((uint8_t*)input, len, digest);
  if (part2)
    for (int i{0}; i < 2016; ++i)
      md5str((uint8_t*)digest, 32, digest);
  return {digest->c[0], digest->c[32]};
}

const uint       GOAL{64}, WINDOW{1000};
const std::regex R3{R"((.)\1\1)"};
const std::regex R5{R"((.)\1\1\1\1)"};

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  md5str_t buf;
  std::vector<int> ind;
  std::map<char, std::vector<int>> threes;
  std::string in;
  std::smatch m;
  std::getline(is, in);
  uint length(in.size()), end{1 << 30};
  in.resize(length + 10);
  if (in.size() > 100000) {
    for (uint val{0}; val < end; ++val) {
      const std::string h{key(in.data(), length + snprintf(&in[length - 1], in.size(), "%d", val) - 1, part2, &buf)};
      for (std::sregex_iterator ri{h.begin(), h.end(), R5}, re; ri != re; ++ri) {
        auto& cur = threes[re->str(1)[0]];
        for (auto i : cur)
          if (val - i > WINDOW)
            if (ind.emplace_back(i), ind.size() == GOAL)
              end = i + WINDOW;
        cur.clear();
      }
      if (std::regex_search(h, m, R3))
        threes[m.str(1)[0]].emplace_back(val);
    }
    std::sort(ind.begin(), ind.end());
    os << ind.at(GOAL - 1) << std::endl;
  }
}
