project(${PROJECT_NAME})


add_library(
	libcore
	core.cpp
	handlers.c
)

target_include_directories(
	libcore
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)