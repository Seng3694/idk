cmake_minimum_required(VERSION 3.3)

project(idk C)

set(IDK_RUN_TESTS ON)

add_subdirectory(ext)
add_subdirectory(engine)

if(IDK_BUILD_TESTS)
	add_subdirectory(test)
endif()

if(IDK_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
