set(HEADER_FILES
	idk_test.h
	core/color_tests.h
	core/file_system_tests.h
	core/matrix4_tests.h
	core/rectangle_tests.h
	core/vector2f_tests.h
	graphics/shader_tests.h
	graphics/window_tests.h
	tiles/tileset_tests.h
)

set(SOURCE_FILES
    main.c
)

include_directories(./)
add_executable(${PROJECT_NAME}_tests ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})

if (IDK_RUN_TESTS)
	add_custom_command(
		TARGET ${PROJECT_NAME}_tests POST_BUILD
		COMMAND ${PROJECT_NAME}_tests
	)
endif()

