project(${PROJECT_NAME})


add_library(
	drivers
	clock.cpp
	gpio.cpp
)

target_include_directories(
	drivers
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)