add_subdirectory (lib)

add_executable (Advent
  Advent.cpp)

target_link_libraries (Advent AdventUtils)
