project(orientnet-test VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

add_executable(test)

target_compile_features(test PRIVATE cxx_std_17)

target_include_directories(test
  PRIVATE
    "${PROJECT_SOURCE_DIR}/../src"
    "${PROJECT_SOURCE_DIR}/.."
)

AUX_SOURCE_DIRECTORY(. SRC)
target_sources(test
  PRIVATE
    "${SRC}"
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(test PRIVATE Threads::Threads)

target_link_libraries(test PRIVATE orientnet)
