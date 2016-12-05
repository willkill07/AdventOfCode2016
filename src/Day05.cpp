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
      int                      length(input.size());
      input.resize(input.size() + 10);
      while (numDone != 8) {
        int  num{-1}, pos{part2 ? -1 : numDone}, len = length - 1 + snprintf(&input[length - 1], input.size(), "%d", index);
        auto digest = md5((uint8_t*)&input[0], len);
        if ((digest[0] & 0x00F0FFFF) == 0) {    // leading zero mask
          num = (digest[0] & 0x000F0000) >> 16; // digest[5] extraction
          if (part2) {
            pos = num, num = digest[0] >> 28; // digest[6] extraction
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
