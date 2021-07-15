project(utility)

add_library(${PROJECT_NAME} STATIC 
    utility.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

