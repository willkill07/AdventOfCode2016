#include "Solution.hpp"
#include "io.hpp"
#include "md5.hpp"
#include <thread>

template <>
void
solve<Day05>(bool part2, std::istream& is, std::ostream& os)
{
  std::string              password{"________"}, input{io::as_string(is)};
  int                      cores = std::thread::hardware_concurrency(), numDone{0};
  std::vector<std::thread> threads;
  for (int c{0}; c < cores; ++c)
    threads.emplace_back([part2, cores, &numDone, &password, &os](std::string input, int index) {
      const static std::string lookup{"0123456789abcdef"};
      int length(input.size());
      input.resize(input.size() + 10);
      while (numDone != 8) {
        int  num{-1}, pos{part2 ? -1 : numDone}, len = length - 1 + snprintf(&input[length - 1], input.size(), "%d", index);
        md5str_t buf;
        md5str((uint8_t*)input.data(), len, &buf);
        if (int{buf.c[0]} + buf.c[1] + buf.c[2] + buf.c[3] + buf.c[4] == 5 * '0') {
          num = buf.c[5] - '0' + (buf.c[5] >= 'a') * (10 + '0' - 'a'); // digest[5] extraction
          if (part2) {
            pos = num, num = buf.c[6] - '0' + (buf.c[6] >= 'a') * (10 + '0' - 'a'); // digest[6] extraction
            if (pos > 7 || password[pos] != '_' || password.find(lookup[num]) != std::string::npos)
              num = -1;
          }
          if (num != -1)
            password[pos] = lookup[num], ++numDone;
        }
        index += cores;
      }
    }, input, c);
  for (auto& t : threads)
    t.join();
  os << password << std::endl;
}
