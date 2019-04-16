project(logging_check)
add_executable(logging_check "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(logging_check PRIVATE logging)
set_target_properties(logging_check PROPERTIES CXX_STANDARD 17)