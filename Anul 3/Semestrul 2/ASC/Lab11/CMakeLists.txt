cmake_minimum_required (VERSION 2.6)
project (SOL-ALL)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
endif ()

# if cmake older (<3.0) use backup findOpenCL
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./cmake-findopencl/)
find_package(OpenCL)

include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARIES})

include_directories(${OPENCL_INCLUDE_DIRS})
link_directories(${OPENCL_LIBRARIES})

add_executable (lab11_bin skl_host.cpp helper.cpp)

# Link the executable to the helper library
target_link_libraries (lab11_bin ${OpenCL_LIBRARY} ${OPENCL_LIBRARIES})

