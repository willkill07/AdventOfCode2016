add_subdirectory(lib)

add_executable(Advent
  Advent.cpp
  Day01.cpp
  Day02.cpp
  Day03.cpp
  Day04.cpp
  Day05.cpp
  Day06.cpp
  Day07.cpp
  Day08.cpp
  Day09.cpp
  Day10.cpp
  Day11.cpp
  Day12.cpp
  Day13.cpp
  Day14.cpp
  Day15.cpp
  Day16.cpp
  Day17.cpp
  Day18.cpp
  Day19.cpp
  Day20.cpp
  Day21.cpp
  Day22.cpp
  Day23.cpp
  Day24.cpp
  Day25.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_compile_options(Advent PUBLIC ${ADVENT_CXX_FLAGS})
target_link_libraries(Advent AdventUtils Threads::Threads -lc++abi)
install(TARGETS Advent RUNTIME DESTINATION ${PROJECT_SOURCE_DIR})
