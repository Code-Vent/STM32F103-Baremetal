project(${PROJECT_NAME})


add_library(
	apps
	pin.cpp
)

target_include_directories(
	apps
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)