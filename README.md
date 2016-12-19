# Advent of Code - 2016

All implementations are written in C++, strictly adhering to C++14 guidelines.

## Prerequisites

* clang (>= 3.5)
* libc++ (>= 3.5)
* CMake (>= 3.1)
* macOS or Linux (only two systems I've tested on)

## Compiling

* A `compile.sh` script is provided
* Just run it and it should be good to go!

## Running

* Invoke `./Advent` to execute all the days
* To run a specific day, invoke `./Advent -f <dayXX>`
* To run a specific part, invoke `./Advent -p <1,2>`
* To see more detailed help, consult `./Advent --help`

## Metrics

* Lines: Number of lines given by `wc`
* Code: `Lines` - `(# preprocessor lines)` - `(lines with no alphanumeric chars)`
* Bytes: Number of total characters
* Chars: Number of non-whitespace characters
* Time: Time in milliseconds to execute each part independently (separate runs)
* Source: link to implementation
* Headers: C++ includes used for solution

## Leaderboard Highlights:

Day | Part 1 | Part 2 | Points
:--:|-------:|-------:|-------:
02  | 31     | 90     | 81
09  | 233    | 66     | 35
10  | 50     | 44     | 108
11  | 112    | 84     | 17
12  | 31     | 19     | 152
13  | 125    | 79     | 22
14  | 145    | 79     | 22
--  |        |        | **437**

## Detailed Information

 Day | Lines | Code | Bytes | Chars | Time (ms) | Source | Headers
:---:|:-----:|:----:|:-----:|:-----:| ---------:|:------:|:-------
01|23|14|594|452|`0.2052`|[Day01.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day01.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `cmath` `set`
02|41|24|1228|936|`0.1100`|[Day02.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day02.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `algorithm` `initializer_list` `type_traits` `utility`
03|26|15|581|452|`3.8843`|[Day03.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day03.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `algorithm` `iterator` `vector`
04|36|26|1059|785|`31.4824`|[Day04.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day04.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) `algorithm` `vector`
05|38|28|1499|1089|`1763.2089`|[Day05.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day05.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) [`md5.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/md5.hpp) `thread`
06|18|12|511|422|`1.0650`|[Day06.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day06.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `algorithm` `array`
07|35|22|931|732|`4.0137`|[Day07.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day07.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) `numeric` `set`
08|45|31|1790|1464|`4.7384`|[Day08.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day08.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `algorithm` `numeric` `regex` `unordered_map` `valarray`
09|21|12|610|526|`7.9737`|[Day09.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day09.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
10|65|47|1829|1425|`4.3627`|[Day10.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day10.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) `map` `set` `vector`
11|15|9|483|412|`0.2393`|[Day11.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day11.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
12|56|38|1869|1446|`0.0647`|[Day12.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day12.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) [`util.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/util.hpp) `algorithm` `array` `vector`
13|34|21|1125|905|`0.1583`|[Day13.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day13.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) `array` `set`
14|53|35|1473|1177|`7268.7253`|[Day14.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day14.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`md5.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/md5.hpp) [`util.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/util.hpp) `algorithm` `map` `regex` `vector`
15|32|21|903|742|`19.9762`|[Day15.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day15.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `regex` `x86intrin.h`
16|45|30|1247|1007|`0.0321`|[Day16.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day16.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) `sstream`
17|47|27|1489|1212|`45.0162`|[Day17.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day17.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp) [`md5.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/md5.hpp) `array` `list`
18|20|13|621|514|`0.8414`|[Day18.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day18.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp)
19|11|5|173|143|`0.0003`|[Day19.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day19.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
20|11|5|173|143|`0.0002`|[Day20.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day20.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
21|11|5|173|143|`0.0002`|[Day21.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day21.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
22|11|5|173|143|`0.0002`|[Day22.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day22.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
23|11|5|173|143|`0.0002`|[Day23.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day23.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
24|11|5|173|143|`0.0002`|[Day24.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day24.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
25|11|5|173|143|`0.0002`|[Day25.cpp](https://github.com/willkill07/adventofcode2016/blob/master/src/Day25.cpp)|[`Solution.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/Solution.hpp) [`io.hpp`](https://github.com/willkill07/adventofcode2016/blob/master/include/io.hpp)
**TOTAL**|**727**|**460**|**21053**|**16699**|**9156.1**| |`  Solution.hpp`&nbsp;<sup>**`25`**</sup> ` io.hpp`&nbsp;<sup>**`16`**</sup> ` algorithm`&nbsp;<sup>**`7`**</sup> ` vector`&nbsp;<sup>**`5`**</sup> ` set`&nbsp;<sup>**`4`**</sup> ` array`&nbsp;<sup>**`4`**</sup> ` regex`&nbsp;<sup>**`3`**</sup> ` md5.hpp`&nbsp;<sup>**`3`**</sup> ` numeric`&nbsp;<sup>**`2`**</sup> ` util.hpp`&nbsp;<sup>**`2`**</sup> ` map`&nbsp;<sup>**`2`**</sup> ` valarray`&nbsp;<sup>**`1`**</sup> ` list`&nbsp;<sup>**`1`**</sup> ` sstream`&nbsp;<sup>**`1`**</sup> ` unordered_map`&nbsp;<sup>**`1`**</sup> ` type_traits`&nbsp;<sup>**`1`**</sup> ` iterator`&nbsp;<sup>**`1`**</sup> ` initializer_list`&nbsp;<sup>**`1`**</sup> ` cmath`&nbsp;<sup>**`1`**</sup> ` x86intrin.h`&nbsp;<sup>**`1`**</sup> ` thread`&nbsp;<sup>**`1`**</sup> ` utility`&nbsp;<sup>**`1`**</sup> ` `
