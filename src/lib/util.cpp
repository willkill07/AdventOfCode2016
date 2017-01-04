#include "util.hpp"

namespace util {

int
htoi(char c)
{
  return c - '0' + (c >= 'a') * (10 + '0' - 'a');
}

char
itoh(int v)
{
  char const digit[] = "0123456789abcdef";
  return digit[v];
}

int
fast_itoa(int i, char* b)
{
  char const digit[] = "0123456789";
  char*      p = b;
  int        shifter = i;
  do
    ++p;
  while (shifter /= 10);
  *p = '\0';
  int dist(p - b);
  do
    *--p = digit[i % 10];
  while (i /= 10);
  return dist;
}

std::vector<std::string>
split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t              start = text.find_first_not_of(delims), end = 0;
  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}
}
