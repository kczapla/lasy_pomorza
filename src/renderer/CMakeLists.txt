add_library(renderer STATIC error.cpp graphics_interface.cpp)
target_sources(renderer
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/buffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/device.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics_interface.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics_interface.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/input_assembler.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/mesh.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/render_target.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/swapchain.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vertex.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.h"
)
target_include_directories(renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(renderer PROPERTIES
    CXX_STANDARD 17)