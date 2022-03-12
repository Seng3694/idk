set(SANDBOX_HEADER_FILES
	include/font.h
	include/text.h
)

set(SANDBOX_SOURCE_FILES
	src/font.c
    src/main.c
	src/text.c
)

include_directories(include)
add_executable(${PROJECT_NAME}_sandbox ${SANDBOX_HEADER_FILES} ${SANDBOX_SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME}_sandbox ${PROJECT_NAME}_engine)

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME}_sandbox POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
