project(trade_simulator)
set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.13.4)
find_package(
		Boost 1.80.0 REQUIRED
		COMPONENTS system filesystem thread unit_test_framework
)

#Bring the headers, such as Student.h into the project
include_directories(include)

# Add core components directory
file(GLOB SOURCES "src/*.cpp")
add_subdirectory(src)

# Add Tests
enable_testing()
file(GLOB_RECURSE test_cases FOLLOW_SYMLINKS "tests/*_test.cpp")

foreach (case ${test_cases})
	## Get filename without extension
	get_filename_component(case_name_we ${case} NAME_WE)
	## Get innermost directory name
    get_filename_component(case_directory ${case} PATH)
    get_filename_component(case_innermost ${case_directory} NAME_WE)
	## Construct executable name
	set(exe_name "${case_innermost}_${case_name_we}")
	## Construct test name
	set(test_name "${exe_name}_test")
	## Add executable and test
	add_executable(${exe_name} ${case})
	target_link_libraries(${exe_name} PRIVATE Boost::unit_test_framework)
	add_test(${test_name} ${exe_name})
ENDFOREACH ()


# Add Entry Point
add_executable(simulator ${SOURCES})
target_link_libraries(simulator PRIVATE Boost::system Boost::filesystem Boost::thread pthread)
target_link_libraries(simulator PUBLIC "-static")

# Add config directory
file(COPY config DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Add input directory
file(COPY input DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
