#include "Solution.hpp"
#include "io.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <mutex>
#include <regex>
#include <set>
#include <vector>

struct LSet {
  std::set<int> v;
  std::mutex    m;
  void
  put(int val)
  {
    std::lock_guard<std::mutex> g{m};
    v.emplace(val);
  }
};

const std::string LOOKUP{"0123456789abcdef"};
const std::regex  R3{R"((.)\1\1)", std::regex::optimize}, R5{R"((.)\1\1\1\1)", std::regex::optimize};
const int         GOAL{64}, WINDOW{1000}, LIMIT{25600};

void
key(const char* input, size_t len, bool part2, md5str_t* digest)
{
  md5str((uint8_t*)input, len, digest);
  for (int i{0}; part2 && i < 2016; ++i)
    md5str((uint8_t*)digest, 32, digest);
}

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  std::array<LSet, 16> l3, l5;
  std::vector<int> ind;
  std::string      in{io::as_string(is)};
  util::parallel_do([&](uint tid, uint N) {
    std::string input{in};
    md5str_t    buf;
    uint32_t    length(input.size());
    input.reserve(length + 10);
    for (uint val{tid}; val < LIMIT; val += N) {
      key(input.data(), length + util::fast_itoa(val, &input[length]), part2, &buf);
      const std::string h{buf.begin(), buf.end()};
      for (auto& m : io::by_match(h, R5))
        l5[LOOKUP.find(m.str(1)[0])].put(val);
      std::smatch m;
      if (std::regex_search(h, m, R3))
        l3[LOOKUP.find(m.str(1)[0])].put(val);
    }
  });
  for (int i{0}; i < 16; ++i)
    for (auto i3 : l3[i].v)
      for (auto i5 : l5[i].v)
        if (i3 < i5 && i5 - i3 < WINDOW) {
          ind.emplace_back(i3);
          break;
        }
  std::sort(ind.begin(), ind.end());
  os << ind[GOAL - 1] << '\t' << std::endl;
}
