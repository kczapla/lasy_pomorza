add_subdirectory(src)

add_executable(simple_triangle WIN32 "${sources}")
target_sources(simple_triangle PUBLIC "${headers}")

target_link_libraries(simple_triangle renderer)
set_target_properties(simple_triangle PROPERTIES CXX_STANDARD 17)

set (shaders_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders")
set (shaders "${shaders_source_dir}/simple_pixel_shader.hlsl" "${shaders_source_dir}/simple_vertex_shader.hlsl")
set (shaders_destination_dir "${CMAKE_CURRENT_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY}resources/shaders")

add_custom_target(shaders ALL ${CMAKE_COMMAND} -E make_directory ${shaders_destination_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${shaders} ${shaders_destination_dir}
    COMMENT "copy shaders sources from ${shaders_source_dir}"
    SOURCES ${shaders}
)