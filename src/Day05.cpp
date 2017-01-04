#include "Solution.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>

template <typename T>
auto
is_value(T val)
{
  return [val](T other) { return other == val; };
}

template <>
void
solve<Day05>(bool part2, std::istream& is, std::ostream& os)
{
  const int   SIZE{8};
  std::string password(SIZE, '_'), in;
  int         numDone{0}, inserted[16];
  std::fill(std::begin(inserted), std::end(inserted), -1);
  is >> in;
  util::parallel_do([&](int groupIdx, int groupSize, std::string input) {
    int length(input.size()), id{groupIdx};
    input.reserve(input.size() + 10);
    md5str_t buf;
    for (; numDone != SIZE; id += groupSize) {
      md5str((uint8_t*)input.data(), length + util::fast_itoa(id, &input[length]), &buf);
      if (!std::all_of(buf.cbegin(), buf.cbegin() + 5, is_value('0')))
        continue;
      int num{util::htoi(buf.c[part2 + 5])}, pos{part2 ? util::htoi(buf.c[5]) : numDone};
      if (part2 && (pos >= SIZE || password[pos] != '_' || inserted[num] != -1))
        continue;
      password[pos] = util::itoh(num), ++numDone, inserted[num] = pos;
    }
  }, in);
  os << password << std::endl;
}
