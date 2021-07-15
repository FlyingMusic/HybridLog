set(bin test_log)

MESSAGE(STATUS "generate make for ${bin}")
add_executable(${bin} main.cpp)
target_link_libraries(${bin} hlog config utility threadpool queue pthread)
add_dependencies(${bin} hlog config utility threadpool queue)
