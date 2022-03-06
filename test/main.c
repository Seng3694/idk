#include "idk_test.h"
#include "core/color_tests.h"
#include "core/file_system_tests.h"
#include "core/matrix4_tests.h"
#include "core/vector2f_tests.h"
#include "graphics/shader_tests.h"
#include "graphics/window_tests.h"

IDK_MAIN(
	CoreColorTests, 
	CoreVector2fTests, 
    CoreMatrix4Tests,
    CoreFileSystemTests
    //GraphicsShaderTests
	//GraphicsWindowTests
);
