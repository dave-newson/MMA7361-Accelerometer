cmake_minimum_required(VERSION 3.2)
project(dynamic-calibration)

set(ENV{PATH} "C:\\Apps\\Python27;C:\\Apps\\Python27\\Scripts;")
set(PLATFORMIO_CMD "C:\\Apps\\Python27\\Scripts\\platformio.exe")

include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/framework-arduinoteensy/cores/teensy3")
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/framework-arduinoteensy/cores/teensy3/avr")
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/framework-arduinoteensy/cores/teensy3/util")
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include")
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.4/include")
include_directories("$ENV{HOMEDRIVE}$ENV{HOMEPATH}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.4/include-fixed")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../src")

add_definitions(-DF_CPU=72000000L)
add_definitions(-DUSB_SERIAL)
add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-D__MK20DX256__)
add_definitions(-DARDUINO=10600)
add_definitions(-DTEENSYDUINO=127)
add_definitions(-DPLATFORMIO=020603)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

#
# Executable
#
add_executable(
        dynamic-calibration
        src/display.cpp
        src/main.cpp
)
