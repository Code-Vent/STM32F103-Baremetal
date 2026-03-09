project(${PROJECT_NAME})

set(EXECUTABLE application_firmware)
set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXAMPLES
    button_test
    uart_transmitter
    uart_receiver
    spi_master
    spi_slave
    i2c_master
    i2c_slave
)

foreach(example ${EXAMPLES})
    add_executable(
        ${example}
        "examples/${example}.cpp"
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/serial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/uart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/spi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/i2c.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/registers/tim.cpp
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