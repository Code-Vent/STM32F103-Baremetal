project(${PROJECT_NAME})


add_library(
	stm32f103
	mcu.cpp
)

target_include_directories(
	stm32f103
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)