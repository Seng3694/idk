include_directories(include)
add_executable(example_shapes_rendering src/shapes_and_rendering.c)
target_link_libraries(example_shapes_rendering ${PROJECT_NAME})

add_executable(example_batch_rendering src/tilemaps_and_batch_rendering.c src/font.c src/text.c include/font.h include/text.h)
target_link_libraries(example_batch_rendering ${PROJECT_NAME})

add_executable(example_physics src/physics.c)
target_link_libraries(example_physics ${PROJECT_NAME})

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET example_shapes_rendering POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET example_batch_rendering POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET example_physics POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
