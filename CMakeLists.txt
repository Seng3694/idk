cmake_minimum_required(VERSION 3.3)

project(idk C)

set(IDK_RUN_TESTS ON)

add_subdirectory(ext)
add_subdirectory(engine)
add_subdirectory(test)
add_subdirectory(game)
