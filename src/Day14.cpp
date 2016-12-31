#include "Solution.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <mutex>
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

void
key(const char* input, size_t len, bool part2, md5str_t* digest)
{
  md5str((uint8_t*)input, len, digest);
  if (part2)
    for (int i{0}; i < 2016; ++i)
      md5str((uint8_t*)digest, 32, digest);
}

template <int N, int Limit, typename Itr, typename Fn>
void
findSeq(Itr begin, Itr end, Fn&& f)
{
  int count{0};
  Itr curr;
  while (std::distance(begin, end) >= N) {
    for (curr = begin + 1; curr != end; ++curr)
      if (*curr != *begin)
        break;
    if (std::distance(begin, curr) >= N) {
      f(*begin);
      if (++count == Limit)
        return;
    }
    begin = curr;
  }
}

const int GOAL{64}, WINDOW{1000}, LIMIT{25600};

template <>
void
solve<Day14>(bool part2, std::istream& is, std::ostream& os)
{
  std::array<LSet, 16> l3, l5;
  std::vector<int> ind;
  std::string      in;
  std::getline(is, in);
  util::parallel_do([&](uint tid, uint N) {
    std::string input{in};
    md5str_t    buf;
    uint32_t    length(input.size());
    input.reserve(length + 10);
    for (uint val{tid}; val < LIMIT; val += N) {
      key(input.data(), length + util::fast_itoa(val, &input[length]), part2, &buf);
      findSeq<5, 32>(buf.cbegin(), buf.cend(), [&](char c) { l5[util::htoi(c)].put(val); });
      findSeq<3, 1>(buf.cbegin(), buf.cend(), [&](char c) { l3[util::htoi(c)].put(val); });
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
