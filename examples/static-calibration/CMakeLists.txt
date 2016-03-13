cmake_minimum_required(VERSION 3.2)
project(static-calibration)

set(ENV{PATH} "C:\\Program Files\\nodejs;D:\\Users\\Vince\\AppData\\Roaming\\npm;D:\\xampp\\php;C:\\Program Files (x86)\\Vagrant\\bin;C:\\Apps\\Android\\sdk\\platform-tools;C:\\Apps\\Android\\sdk\\tools;C:\\Users\\Vince\\bin;C:\\Apps\\Git\\mingw64\\bin;C:\\Apps\\Git\\usr\\local\\bin;C:\\Apps\\Git\\usr\\bin;C:\\Apps\\Git\\usr\\bin;C:\\Apps\\Git\\mingw64\\bin;C:\\Apps\\Git\\usr\\bin;C:\\Users\\Vince\\bin;C:\\ProgramData\\Oracle\\Java\\javapath;C:\\Apps\\Python27;C:\\Apps\\Python27\\Scripts;C:\\Windows\\system32;C:\\Windows;C:\\Windows\\System32\\Wbem;C:\\Windows\\System32\\WindowsPowerShell\\v1.0;C:\\Apps\\Vagrant\\bin;C:\\Program Files (x86)\\NVIDIA Corporation\\PhysX\\Common;C:\\Program Files (x86)\\Windows Phone TShell;C:\\Program Files (x86)\\Windows Kits\\8.1\\Windows Performance Toolkit;C:\\Apps\\xampp\\php;C:\\ProgramData\\ComposerSetup\\bin;C:\\Apps\\nodejs;C:\\Program Files\\7-zip;C:\\Apps\\NSIS;C:\\Program Files\\Common Files\\Autodesk Shared;C:\\Program Files (x86)\\Autodesk\\Backburner;C:\\Windows\\system32;C:\\Windows;C:\\Windows\\System32\\Wbem;C:\\Windows\\System32\\WindowsPowerShell\\v1.0;C:\\Apps\\Vagrant\\bin;C:\\Program Files (x86)\\NVIDIA Corporation\\PhysX\\Common;C:\\Users\\Vince\\AppData\\Roaming\\npm;C:\\Apps\\Git\\usr\\bin\\vendor_perl;C:\\Apps\\Git\\usr\\bin\\core_perl")
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
# Main
#
add_executable(
        static-calibration
        src/main.cpp
        src/display.cpp
)
