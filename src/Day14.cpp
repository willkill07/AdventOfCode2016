#include "Solution.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <mutex>
#include <regex>
#include <set>
#include <thread>
#include <vector>

void
key(const char* input, size_t len, bool part2, md5str_t* digest)
{
  md5str((uint8_t*)input, len, digest);
  if (part2)
    for (int i{0}; i < 2016; ++i)
      md5str((uint8_t*)&(digest->c[0]), 32, digest);
}

const int         GOAL{64}, WINDOW{1000}, LIMIT{25600};
const std::string LOOKUP{"0123456789abcdef"};
const std::regex  R3{R"((.)\1\1)", std::regex::optimize};
const std::regex  R5{R"((.)\1\1\1\1)", std::regex::optimize};

struct LSet {
  std::set<int> v;
  std::mutex m;
};

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  std::vector<std::thread> threads;
  std::array<LSet, 16> l3, l5;
  std::vector<int> ind;
  std::string      in;
  is >> in;

  for (uint tid{0}; tid < std::thread::hardware_concurrency(); ++tid) {
    threads.emplace_back([&] (uint tid) {
      std::string input{in};
      md5str_t buf;
      uint length(input.size());
      input.resize(length + 10);
      for (uint val{tid}; val < LIMIT; val += std::thread::hardware_concurrency()) {
        key(input.data(), length + util::fast_itoa(val, &input[length]), part2, &buf);
        const std::string h{buf.begin(), buf.end()};
        for (std::sregex_iterator ri{h.begin(), h.end(), R5}, re{}; ri != re; ++ri) {
          auto& curr = l5[LOOKUP.find(ri->str(1)[0])];
          curr.m.lock(), curr.v.emplace(val), curr.m.unlock();
        }
        std::smatch m;
        if (std::regex_search(h, m, R3)) {
          auto& curr = l3[LOOKUP.find(m.str(1)[0])];
          curr.m.lock(), curr.v.emplace(val), curr.m.unlock();
        }
      }
    }, tid);
  }
  for (auto& t : threads)
    t.join();
  for (uint i{0}; i < 16; ++i)
    for (auto i5 : l5[i].v)
      for (auto i3 : l3[i].v)
        if (i3 < i5 && i3 + WINDOW >= i5)
          ind.emplace_back(i3);
  std::sort(ind.begin(), ind.end());
  os << ind[GOAL - 1] << '\t' << std::endl;
}
