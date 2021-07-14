project(core)

add_library(${PROJECT_NAME} STATIC 
    hlog.cpp
    hlog-imp.cpp
    ThreadPool.cpp
    hlog-factory.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

