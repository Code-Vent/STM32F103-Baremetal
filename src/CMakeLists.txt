project(${PROJECT_NAME})

set(EXECUTABLE application_firmware)
set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXAMPLES
    button_test
)

foreach(example ${EXAMPLES})
    add_executable(
        ${example}
        "examples/${example}.cpp"
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/apps/button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f103/mcu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcore/core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libcore/handlers.c
        ${PROGRAM_START_UP}
    )
    set_target_properties(${example} PROPERTIES SUFFIX ".elf")
    target_include_directories(${example} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})

    target_compile_options(
        ${example} PRIVATE
        ${CPU_PARAMETERS}
        ${SOURCE_COMPILE_OPTIONS}
    )

    target_link_options(${example} PRIVATE
        -T${MCU_LINKER_SCRIPT}
        ${CPU_PARAMETERS}
        ${MCU_LINKER_OPTIONS}
        -Wl,-Map=${example}.map
    )
endforeach()