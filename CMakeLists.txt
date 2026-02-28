cmake_minimum_required(VERSION 3.20)
project(term_project_group_7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- server ----
add_executable(server
    src/server.cpp
    src/menu/menu.cpp
    src/menu/addition_menu.cpp
    src/problem/addition_problem.cpp
    src/problem/addition_problem_generator.cpp
)

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
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
  tests/test_addition_problems.cpp
  tests/test_addition_problem_generator.cpp
  src/problem/addition_problem.cpp
  src/problem/addition_problem_generator.cpp
)

target_include_directories(test_health PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

if (WIN32)
  target_link_libraries(test_health PRIVATE ws2_32)
endif()

add_test(NAME health COMMAND test_health)

# --- MVP behavior test added ---
add_executable(test_mvp_service tests/test_mvp_service.cpp)

target_include_directories(test_mvp_service PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

if (WIN32)
  target_link_libraries(test_mvp_service PRIVATE ws2_32)
endif()

add_test(NAME mvp_service COMMAND test_mvp_service)