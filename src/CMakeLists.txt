
SET(MODULES hlog hconfig queue threadpool utility cjson logclient netclient)
foreach(module ${MODULES})
    MESSAGE(STATUS "generate module ${module}")
    add_subdirectory(${module})
endforeach()
