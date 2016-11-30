#ifndef _WILLIAM_KILLIAN_SOLUTION_HPP_
#define _WILLIAM_KILLIAN_SOLUTION_HPP_

#include <fstream>
#include <iostream>
#include <string>

enum Day {
  Day01,
  Day02,
  Day03,
  Day04,
  Day05,
  Day06,
  Day07,
  Day08,
  Day09,
  Day10,
  Day11,
  Day12,
  Day13,
  Day14,
  Day15,
  Day16,
  Day17,
  Day18,
  Day19,
  Day20,
  Day21,
  Day22,
  Day23,
  Day24,
  Day25,
  TOTAL_DAYS
};

std::string
asString(Day d);

template <Day DAY>
void
solve(bool part2, std::istream& is, std::ostream& os)
{
  os << asString(DAY) << " part " << (part2 ? '2' : '1') << " is not implemented";
  if (is.bad())
    os << " and input file does not exist" << std::endl;
  else
    os << std::endl;
};

#endif
