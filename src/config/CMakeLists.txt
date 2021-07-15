project(config)

add_library(${PROJECT_NAME} STATIC 
    Config.cpp
    libconfigcpp.c++
    wincompat.h
    grammar.c
    scanner.c
    scanctx.c
    parsectx.h
    libconfig.c
    strbuf.c
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

