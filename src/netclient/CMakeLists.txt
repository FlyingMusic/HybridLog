project(netclient)

add_library(${PROJECT_NAME} STATIC 
    NetClient.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

