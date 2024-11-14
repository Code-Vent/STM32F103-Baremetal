project(${PROJECT_NAME})

set(EXECUTABLE application_firmware)
set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set_property(SOURCE foo.s APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
#add_executable(hello foo.s bar.c)


add_executable(
	${EXECUTABLE}
 clock.cpp
 gpio.cpp
 mcu.cpp
 main.cpp
 ${PROGRAM_START_UP}
)

set_target_properties(${EXECUTABLE} PROPERTIES SUFFIX ".elf")


target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})

#message(FATAL_ERROR ${PROJECT_INCLUDE_DIRECTORIES})
###############################################################################

target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    ${SOURCE_COMPILE_OPTIONS}
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    ${MCU_LINKER_OPTIONS}
    -Wl,-Map=${EXECUTABLE}.map
)

###############################################################################

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
     COMMAND ${CMAKE_OBJDUMP} -D -C $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s
    COMMAND "openocd" -f "interface/stlink-v2.cfg" -f "board/stm32f103c8_blue_pill.cfg"
)
