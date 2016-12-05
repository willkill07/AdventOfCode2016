add_library(AdventUtils
  io.cpp
  Solution.cpp
  md5.cpp)

target_compile_options(AdventUtils PUBLIC ${ADVENT_CXX_FLAGS})
