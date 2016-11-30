#include "io.hpp"

namespace io {

namespace detail {
  std::istream&
  operator>>(std::istream& i, line& l)
  {
    return std::getline(i, l);
  }
}

std::sregex_iterator
re_search(const std::string& str, const std::regex& re)
{
  return {std::begin(str), std::end(str), re};
}

std::string
as_string(std::istream& is)
{
  return {std::istreambuf_iterator<char>{is}, {}};
}

by_match::by_match(const std::string& str, const std::regex& re)
  : bi{re_search(str, re)}
  , ei{}
{
}

std::sregex_iterator
by_match::begin()
{
  return bi;
}

std::sregex_iterator
by_match::end()
{
  return ei;
}

int
to_int(const std::string& s)
{
  return std::stoi(s);
}

std::smatch
regex_parse(const std::string& str, const std::regex& re)
{
  std::smatch res;
  std::regex_match(str, res, re);
  return res;
}
}
