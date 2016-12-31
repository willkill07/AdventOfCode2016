#include "Solution.hpp"
#include "md5.hpp"
#include "util.hpp"
#include <algorithm>

const static std::string LOOKUP{"0123456789abcdef"};

template <>
void
solve<Day05>(bool part2, std::istream& is, std::ostream& os)
{
  std::string password{"________"}, input;
  int         numDone{0}, inserted[16];
  std::getline(is, input);
  std::fill(std::begin(inserted), std::end(inserted), -1);
  util::parallel_do([&](int groupIdx, int groupSize, std::string input) {
    md5str_t buf;
    int      length(input.size()), id{groupIdx};
    input.reserve(input.size() + 10);
    for (; numDone != 8; id += groupSize) {
      int num{-1}, pos{numDone};
      md5str((uint8_t*)input.data(), length + util::fast_itoa(id, &input[length]), &buf);
      if (std::count(buf.cbegin(), buf.cbegin() + 5, '0') != 5)
        continue;
      num = util::htoi(buf.c[5]);
      if (part2) {
        pos = num, num = util::htoi(buf.c[6]);
        if (pos > 7 || password[pos] != '_' || inserted[num] != -1)
          continue;
      }
      password[pos] = LOOKUP[num], ++numDone, inserted[num] = pos;
    }
  }, input);
  os << password << std::endl;
}
