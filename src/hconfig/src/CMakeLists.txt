project(hconfig)

add_library(${PROJECT_NAME} STATIC 
    Config.cpp
    hconfig.cpp
    hconfig-factory.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} config)
add_subdirectory(thirdlib)

