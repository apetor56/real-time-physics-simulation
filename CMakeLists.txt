cmake_minimum_required(VERSION 3.19)
project(CollisionDetection VERSION 1.0)

add_subdirectory(source)

if (CMAKE_GENERATOR MATCHES "Visual Studio")   
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
