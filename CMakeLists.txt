cmake_minimum_required(VERSION 3.20)
project(term_project_group_7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- server ----
add_executable(server
    src/server.cpp
)

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Windows sockets library (needed for cpp-httplib on Windows)
if (WIN32)
  target_link_libraries(server PRIVATE ws2_32)
endif()

# Copy static/ next to the built exe so "/" can serve index.html
add_custom_command(TARGET server POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/static
    $<TARGET_FILE_DIR:server>/static
)

# ---- tests ----
enable_testing()

add_executable(test_health
  tests/test_health.cpp
)

target_include_directories(test_health PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

if (WIN32)
  target_link_libraries(test_health PRIVATE ws2_32)
endif()

add_test(NAME health COMMAND test_health)