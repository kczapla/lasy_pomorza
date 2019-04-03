add_subdirectory(src)

add_executable(simple_triangle WIN32 "${sources}")
target_sources(simple_triangle PUBLIC "${headers}")

target_link_libraries(simple_triangle renderer)
set_target_properties(simple_triangle PROPERTIES CXX_STANDARD 17)

set (source "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY}/resources")
add_custom_command(
    TARGET simple_triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination}
    COMMENT "copy resource folder from ${source} to ${destination}"
)