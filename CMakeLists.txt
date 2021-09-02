cmake_minimum_required(VERSION 3.10)

project(bulk CXX)

add_executable(bulk main.cpp)
add_library(bulk_handler bulk_handler.cpp)

target_include_directories(bulk PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bulk PRIVATE
    bulk_handler
)

target_compile_features(bulk_handler PUBLIC cxx_std_17)
target_compile_features(bulk PUBLIC cxx_std_17)
