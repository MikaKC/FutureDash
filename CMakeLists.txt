cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(better-gmd)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(better-gmd SHARED ${SOURCE_FILES})

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#69e969c")
CPMAddPackage("gh:HJfod/cocos-headers#cbf79fc")
CPMAddPackage("gh:HJfod/gd.h#90f2110")
CPMAddPackage("gh:TsudaKageyu/minhook#4a45552")

target_compile_definitions(better-gmd PRIVATE CC_DLL=)

target_include_directories(better-gmd PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
)

target_link_libraries(better-gmd mat-dash cocos2d minhook)
