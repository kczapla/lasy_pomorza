set(TARGET_NAME logging)
project(${TARGET_NAME})
add_library(${TARGET_NAME} STATIC "${CMAKE_CURRENT_SOURCE_DIR}/logging.hpp")
target_sources(${TARGET_NAME} 
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_loguru.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_loguru.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_stdio.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_stdio.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_interface.hpp"
)
target_include_directories(${TARGET_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${TARGET_NAME} PRIVATE loguru)
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 LINKER_LANGUAGE CXX)