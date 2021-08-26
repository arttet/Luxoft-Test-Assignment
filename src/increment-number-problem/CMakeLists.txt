project(increment-number-problem)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Boost::headers
    fmt::fmt
    Microsoft.GSL::GSL

    increment_number_problem
)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
)

add_test(
  NAME ${PROJECT_NAME}_with_wrong_first_arg
  COMMAND ${PROJECT_NAME} "-2048"
)

add_test(
  NAME ${PROJECT_NAME}_with_wrong_second_arg
  COMMAND ${PROJECT_NAME} "2048" "-1"
)

set_tests_properties(
  ${PROJECT_NAME}_with_wrong_first_arg
  ${PROJECT_NAME}_with_wrong_second_arg
  PROPERTIES WILL_FAIL TRUE
)
