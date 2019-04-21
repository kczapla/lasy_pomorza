set(TARGET_NAME logging)
project(${TARGET_NAME})
add_library(${TARGET_NAME} STATIC)
target_sources(${TARGET_NAME} 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/logging.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging.cpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logger.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_loguru.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_loguru.cpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_stdio.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_stdio.cpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_policy.hpp"    
)

target_include_directories(${TARGET_NAME} 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${TARGET_NAME} PRIVATE loguru)
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 LINKER_LANGUAGE CXX)