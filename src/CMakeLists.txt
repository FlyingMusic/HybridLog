
SET(MODULES hlog config queue threadpool utility)
foreach(module ${MODULES})
    MESSAGE(STATUS "generate module ${module}")
    add_subdirectory(${module})
endforeach()
