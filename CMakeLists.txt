cmake_minimum_required(VERSION 3.14)
# Project information
project(CircularBuffer
  VERSION 5.0.0
  DESCRIPTION "Circular buffer library."
  LANGUAGES CXX
)
# Add the library target
add_library(circle_buf INTERFACE)
# Setup include directories 
target_include_directories(circle_buf INTERFACE src/)

# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Add the example target
  add_executable(circle_buf_example examples/cmake/circle_buf_example.cc)
  # Add the includes
  target_include_directories(circle_buf_example PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the example target
  target_link_libraries(circle_buf_example
    PRIVATE 
      circle_buf
  )
  # Fetch google test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()
  include(GoogleTest)
  # Add the test target
  add_executable(circle_buf_test tests/circle_buf_test.cc)
  # Add the includes
  target_include_directories(circle_buf_test PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the test target
  target_link_libraries(circle_buf_test
    PRIVATE 
      circle_buf
      gtest_main 
      gtest
      gmock
  )
  # Discover unit tests
  gtest_discover_tests(circle_buf_test)
endif()