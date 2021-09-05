project(knights_tour_problem)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    include/knights_tour_problem/knights_tour_problem.hpp

    src/knights_tour_problem.cpp
)

include(GenerateExportHeader)
GENERATE_EXPORT_HEADER(${PROJECT_NAME}
    EXPORT_FILE_NAME _public/${PROJECT_NAME}/export.h
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/_public>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Boost::headers
    Threads::Threads
)
