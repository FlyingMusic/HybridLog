project(logclient)

add_library(${PROJECT_NAME} STATIC 
    LogClient.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} netclient)

