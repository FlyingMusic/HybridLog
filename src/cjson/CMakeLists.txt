project(cjson)

add_library(${PROJECT_NAME} STATIC 
    cJSON.c
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

