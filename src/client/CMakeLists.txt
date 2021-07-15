project(hlog)

add_library(${PROJECT_NAME} STATIC 
    hlog.cpp
    hlog-factory.cpp
    hlog-imp.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} threadpool queue utility)

