#include "Preprocessor.hpp"
#include "Solution.hpp"
#include "timer.hpp"
#include <array>
#include <getopt.h>
#include <iomanip>
#include <regex>

enum time_options_t { NO_TIME = 0, TIME_IND = 1, TIME_TOTAL = 2 };

struct options_t {
  bool           part1{true}, part2{true};
  time_options_t time{NO_TIME};
  std::regex     filter{".*"};
};

template <Day>
double
timeSolve(bool, bool);

double
run(Day, bool, time_options_t, std::ostream&);

options_t
parseArgs(int, char* []);

int
main(int argc, char* argv[])
{
  std::ofstream DEVNULL{"/dev/null"};
  options_t     options = parseArgs(argc, argv);
  double        totalTime{0.0};
  std::ostream  os{options.time == TIME_TOTAL ? DEVNULL.rdbuf() : std::cout.rdbuf()};
  for (int d{Day01}; d != TOTAL_DAYS; ++d) {
    Day day{static_cast<Day>(d)};
    if (!std::regex_search(asString(day), options.filter))
      continue;
    os << asString(day) << ((options.part1 && options.part2) ? "\n" : ": ");
    if (options.part1) {
      if (options.part2)
        os << "Part 1: ";
      totalTime += run(day, false, options.time, os);
    }
    if (options.part2) {
      if (options.part1)
        os << "Part 2: ";
      totalTime += run(day, true, options.time, os);
    }
  }
  if (options.time == TIME_TOTAL)
    printf("  time: %.5lfms\n", totalTime);
  return EXIT_SUCCESS;
}

template <Day DAY>
double
timeSolve(bool part2, bool time, std::ostream& os)
{
  double        resTime{0.0};
  std::ifstream is{"./inputs/" + asString(DAY) + ".txt"};
  if (time) {
    Timer t;
    solve<DAY>(part2, is, os);
    resTime = t.current();
    os.precision(5);
    os << "  time: ";
    os.setf(std::ios::fixed, std::ios::floatfield);
    os << resTime << "ms" << std::endl;
  } else
    solve<DAY>(part2, is, os);
  return resTime;
}

#define RUN_DAY(X) \
  case Day##X:     \
    return timeSolve<Day##X>(part2, time, os);
double
run(Day day, bool part2, time_options_t time, std::ostream& os)
{
  switch (day) {
    EVAL(MAP(RUN_DAY, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25))
    default:
      return 0.0;
  }
}
#undef RUN_DAY

options_t
parseArgs(int argc, char* argv[])
{
  options_t                options;
  static char const* const shortOpts{"htnp:f:"};
  static const std::array<const ::option, 6> longOpts{{{"help", no_argument, nullptr, 'h'},
                                                       {"part", required_argument, nullptr, 'p'},
                                                       {"filter", required_argument, nullptr, 'f'},
                                                       {"time", required_argument, nullptr, 't'},
                                                       {nullptr, 0, nullptr, 0}}};
  int option{0};
  while ((option = getopt_long(argc, argv, shortOpts, longOpts.data(), nullptr)) != -1) {
    switch (option) {
      case 'p':
        if (optarg[0] == '1')
          options.part2 = false;
        else if (optarg[0] == '2')
          options.part1 = false;
        break;
      case 'f':
        options.filter = std::regex{optarg};
        break;
      case 't': {
        std::string arg{optarg};
        const static std::vector<std::string> timeOptStrings{"no", "yes", "total"};
        long index{std::distance(timeOptStrings.begin(), std::find(timeOptStrings.begin(), timeOptStrings.end(), arg))};
        if (index != 3) {
          options.time = static_cast<time_options_t>(index);
          break;
        }
        printf("ERROR: invalid time specified\n");
      }
      case 'h':
      case '?':
        printf("Advent of Code - 2015\n"
               "---------------------\n"
               " -h|--help )\n    print help\n"
               " -p|--part=[1,2,all] )\n    only run parts specified [default = all]\n"
               " -f|--filter=<regex> )\n    filter day on regular expression [default = match all]\n"
               " -t|--time=[no,yes,total] )\n print timing of exection [default = no]\n"
               "\n"
               " Implementation by William Killian (c) 2016\n");
        exit(EXIT_SUCCESS);
        break;
    }
  }
  return options;
}
