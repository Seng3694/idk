
set(HEADER_FILES
	include/idk/core/color.h
	include/idk/core/common.h
	include/idk/core/file_system.h
	include/idk/core/gamepad_state.h
	include/idk/core/keys.h
	include/idk/core/matrix4.h
	include/idk/core/mouse_buttons.h
	include/idk/core/rectangle.h
	include/idk/core/rectangle.inl
	include/idk/core/vector2f.h
	include/idk/core/vector2f.inl
	include/idk/graphics/camera.h
	include/idk/graphics/primitives_renderer.h
	include/idk/graphics/shader.h
	include/idk/graphics/sprite_renderer.h
	include/idk/graphics/texture.h
	include/idk/graphics/window.h
	include/idk/tiles/tilemap.h
	include/idk/tiles/tileset.h
)

set(SOURCE_FILES
	src/core/color.c
	src/core/file_system.c
	src/core/matrix4.c
	src/core/rectangle.c
	src/core/vector2f.c
	src/graphics/camera.c
	src/graphics/primitives_renderer.c
	src/graphics/shader.c
	src/graphics/sprite_renderer.c
	src/graphics/texture.c
	src/graphics/window.c
	src/tiles/tilemap.c
	src/tiles/tileset.c
)

add_library(${PROJECT_NAME}_engine ${HEADER_FILES} ${SOURCE_FILES} )
target_include_directories(${PROJECT_NAME}_engine PUBLIC include)

target_link_libraries(${PROJECT_NAME}_engine glad)
target_link_libraries(${PROJECT_NAME}_engine glfw)
target_link_libraries(${PROJECT_NAME}_engine stb)
