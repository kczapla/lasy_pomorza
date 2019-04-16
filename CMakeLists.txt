cmake_minimum_required (VERSION 3.12)
project (lasy_pomorza)

set(CMAKE_MODULES "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULES})

add_subdirectory(src)
add_subdirectory(examples)


include(update_git_submodules RESULT_VARIABLE rv)
update_git_submodules()
add_subdirectory(external)