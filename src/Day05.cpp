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
    int      length(input.size() - 1), id{groupIdx};
    input.reserve(input.size() + 10);
    while (numDone != 8) {
      int num{-1}, pos{part2 ? -1 : numDone};
      md5str((uint8_t*)input.data(), length + util::fast_itoa(id, &input[length]), &buf);
      if (std::string{buf.begin(), buf.begin() + 5} == "00000") {
        num = util::htoi(buf.c[5]);
        if (part2) {
          pos = num, num = util::htoi(buf.c[6]);
          if (pos > 7 || password[pos] != '_' || password.find(LOOKUP[num]) != std::string::npos)
            num = -1;
        }
        if (num != -1)
          password[pos] = LOOKUP[num], ++numDone;
      }
      id += groupSize;
    }
  }, input);
  os << password << std::endl;
}
