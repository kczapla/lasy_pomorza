set (sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/device_resources.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/framework_window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp"
    PARENT_SCOPE)

set (headers 
    "${CMAKE_CURRENT_SOURCE_DIR}/cube_model.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/device_resources.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/framework_entry.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/framework_window.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/renderer.h"
    PARENT_SCOPE)