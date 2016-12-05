#include "Solution.hpp"
#include "io.hpp"
#include "md5.hpp"

template <>
void
solve<Day05>(bool part2, std::istream& is, std::ostream& os)
{
  std::string password{"________"}, lookup{"0123456789abcdef"}, input{io::as_string(is)};
  int         length(input.size()), index{0};
  input.resize(input.size() + 10);
  for (int i{0}; i < 8; ++i) {
    int num{-1}, pos{part2 ? -1 : i};
    while (num == -1) {
      int  len = length - 1 + snprintf(&input[length - 1], input.size(), "%d", ++index);
      auto digest = md5((uint8_t*)&input[0], len);
      if ((digest[0] & 0x00F0FFFF) == 0) {    // leading zero mask
        num = (digest[0] & 0x000F0000) >> 16; // digest[5] extraction
        if (part2) {
          pos = num, num = digest[0] >> 28; // digest[6] extraction
          if (pos > 7 || password[pos] != '_' || password.find(lookup[num]) != std::string::npos)
            num = -1;
        }
      }
    }
    password[pos] = lookup[num];
    // os << password << std::endl; // uncomment for video!
  }
  os << password << std::endl;
}
