#include "Solution.hpp"
#include "io.hpp"
#include "md5.hpp"
#include "util.hpp"

const static std::string LOOKUP{"0123456789abcdef"};

template <>
void
solve<Day05>(bool part2, std::istream& is, std::ostream& os)
{
  std::string password{"________"}, input{io::as_string(is)};
  int         numDone{0};
  util::parallel_do([part2, &numDone, &password, &os](int groupIdx, int groupSize, std::string input) {
    md5str_t buf;
    int      length(input.size());
    input.reserve(input.size() + 10);
    while (numDone != 8) {
      int num{-1}, pos{part2 ? -1 : numDone};
      md5str((uint8_t*)input.data(), length - 1 + util::fast_itoa(groupIdx, &input[length - 1]), &buf);
      if (int{buf.c[0]} + buf.c[1] + buf.c[2] + buf.c[3] + buf.c[4] == 5 * '0') {
        num = buf.c[5] - '0' + (buf.c[5] >= 'a') * (10 + '0' - 'a'); // digest[5] extraction
        if (part2) {
          pos = num, num = buf.c[6] - '0' + (buf.c[6] >= 'a') * (10 + '0' - 'a'); // digest[6] extraction
          if (pos > 7 || password[pos] != '_' || password.find(LOOKUP[num]) != std::string::npos)
            num = -1;
        }
        if (num != -1)
          password[pos] = LOOKUP[num], ++numDone;
      }
      groupIdx += groupSize;
    }
  }, input);
  os << password << std::endl;
}
