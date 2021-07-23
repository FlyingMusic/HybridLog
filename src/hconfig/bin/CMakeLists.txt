set(bin test_hconfig)

MESSAGE(STATUS "generate make for ${bin}")
add_executable(${bin} main.cpp)
target_link_libraries(${bin} hconfig)
add_dependencies(${bin} hconfig)
