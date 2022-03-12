set(HEADER_FILES
)

set(SOURCE_FILES
    src/main.c
)

include_directories(include)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_engine)

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
