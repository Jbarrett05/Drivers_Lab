cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(level_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(level
  libraries/LIS3DH.cpp
  libraries/LIS3DH.h
  libraries/NeoMatrix.h
  libraries/NeoMatrix.pio
  libraries/NeoMatrix.cpp
  src/level.cpp
)

pico_enable_stdio_usb(level 1)

pico_add_extra_outputs(level)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(level ${CMAKE_CURRENT_LIST_DIR}/libraries/NeoMatrix.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/libraries/generated)


target_link_libraries(level 
  pico_stdlib
  hardware_i2c
  hardware_pio
)