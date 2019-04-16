project(logging)
add_library(logging STATIC)
target_sources(logging PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/logging.hpp")
target_sources(logging 
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_loguru.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_loguru.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_stdio.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/logging_stdio.cpp"
)
target_link_libraries(logging PRIVATE loguru)
target_include_directories(logging PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(logging PROPERTIES CXX_STANDARD 17)