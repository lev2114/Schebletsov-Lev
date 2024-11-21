cmake_minimum_required(VERSION 3.20)

project(Example)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MassiveSort.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/MassiveSort.hpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)
add_custom_target(
    clang-tidy
    COMMAND clang-tidy
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)
