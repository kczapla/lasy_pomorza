cmake_minimum_required (VERSION 3.12)
project (lasy_pomorza)
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

set(CMAKE_MODULES "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULES})

include(update_git_submodules RESULT_VARIABLE rv)
update_git_submodules()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)
# mark_as_advanced(
#     BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
#     gmock_build_tests gtest_build_samples gtest_build_tests
#     gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
# )