set(bin test_log)

MESSAGE(STATUS "generate make for ${bin}")
add_executable(${bin} main.cpp)
target_link_libraries(${bin} core pthread)
add_dependencies(${bin} core)
