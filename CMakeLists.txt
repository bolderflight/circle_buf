cmake_minimum_required(VERSION 3.13)
# Project information
project(CIRCULAR_BUFFER
	VERSION 1.0
	DESCRIPTION "Circular buffer"
	LANGUAGES C CXX
)
# Add the library target
add_library(circle_buf
	src/circle_buf/circle_buf.cc
	include/circle_buf/circle_buf.h
)
# Setup include directories 
target_include_directories(circle_buf PUBLIC 
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)
# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(circle_buf_example examples/circle_buf_example.cc)
	# Add the includes
	target_include_directories(circle_buf_example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the example target
	target_link_libraries(circle_buf_example
		PRIVATE 
			circle_buf
	)
endif()