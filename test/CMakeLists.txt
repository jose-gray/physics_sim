cmake_minimum_required(VERSION 3.20)

set(This PersonalTrainingTests)

file(GLOB TestSources *.cpp)

add_executable(${This} ${TestSources} ${Sources})
target_link_libraries(${This} PUBLIC raylib)
target_link_libraries(${This} PUBLIC gtest_main)

add_test(
  NAME ${This}
  COMMAND ${This}
) 