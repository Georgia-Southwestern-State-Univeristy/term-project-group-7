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
    src/menu/subtraction_menu.cpp
    src/problem/subtraction_problem.cpp
    src/problem/subtraction_problem_generator.cpp
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
  tests/test_subtraction_problems.cpp
  tests/test_subtraction_problem_generator.cpp
  src/problem/subtraction_problem.cpp
  src/problem/subtraction_problem_generator.cpp
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

# --- Week 7: additional demo-path tests (4 required) ---

add_executable(test_happy_high_score_rules tests/test_happy_high_score_rules.cpp)
target_include_directories(test_happy_high_score_rules PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_happy_high_score_rules PRIVATE ws2_32)
endif()
add_test(NAME happy_high_score_rules COMMAND test_happy_high_score_rules)

add_executable(test_happy_grade_level_boundaries tests/test_happy_grade_level_boundaries.cpp)
target_include_directories(test_happy_grade_level_boundaries PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_happy_grade_level_boundaries PRIVATE ws2_32)
endif()
add_test(NAME happy_grade_level_boundaries COMMAND test_happy_grade_level_boundaries)

add_executable(test_failure_invalid_score tests/test_failure_invalid_score.cpp)
target_include_directories(test_failure_invalid_score PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_failure_invalid_score PRIVATE ws2_32)
endif()
add_test(NAME failure_invalid_score COMMAND test_failure_invalid_score)

add_executable(test_boundary_score_70_cutoff tests/test_boundary_score_70_cutoff.cpp)
target_include_directories(test_boundary_score_70_cutoff PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_boundary_score_70_cutoff PRIVATE ws2_32)
endif()
add_test(NAME boundary_score_70_cutoff COMMAND test_boundary_score_70_cutoff)

# --- Week 10 tests ---

add_executable(test_auth_teacher_override_unauthorized tests/test_auth_teacher_override_unauthorized.cpp)
target_include_directories(test_auth_teacher_override_unauthorized PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_auth_teacher_override_unauthorized PRIVATE ws2_32)
endif()
add_test(NAME auth_teacher_override_unauthorized COMMAND test_auth_teacher_override_unauthorized)

add_executable(test_auth_teacher_override_authorized tests/test_auth_teacher_override_authorized.cpp)
target_include_directories(test_auth_teacher_override_authorized PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_auth_teacher_override_authorized PRIVATE ws2_32)
endif()
add_test(NAME auth_teacher_override_authorized COMMAND test_auth_teacher_override_authorized)

add_executable(test_validation_teacher_override_missing_reason tests/test_validation_teacher_override_missing_reason.cpp)
target_include_directories(test_validation_teacher_override_missing_reason PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_validation_teacher_override_missing_reason PRIVATE ws2_32)
endif()
add_test(NAME validation_teacher_override_missing_reason COMMAND test_validation_teacher_override_missing_reason)

add_executable(test_refactor_assessment_missing_skill tests/test_refactor_assessment_missing_skill.cpp)
target_include_directories(test_refactor_assessment_missing_skill PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_refactor_assessment_missing_skill PRIVATE ws2_32)
endif()
add_test(NAME refactor_assessment_missing_skill COMMAND test_refactor_assessment_missing_skill)

add_executable(test_regression_unknown_student_recommendation tests/test_regression_unknown_student_recommendation.cpp)
target_include_directories(test_regression_unknown_student_recommendation PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)
if (WIN32)
  target_link_libraries(test_regression_unknown_student_recommendation PRIVATE ws2_32)
endif()
add_test(NAME regression_unknown_student_recommendation COMMAND test_regression_unknown_student_recommendation)
