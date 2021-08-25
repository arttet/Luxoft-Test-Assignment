project(knights-tour-problem)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    fmt::fmt
    Microsoft.GSL::GSL
)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
)
