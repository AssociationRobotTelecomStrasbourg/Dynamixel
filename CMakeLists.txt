cmake_minimum_required(VERSION 2.8.3)

project(ARTS_Dynamixel)

find_package(Curses REQUIRED)

include_directories(include dynamixel_sdk_c/include/dynamixel_sdk)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

set(dxl_files
    dynamixel_sdk_c/src/dynamixel_sdk/group_bulk_read.c
    dynamixel_sdk_c/src/dynamixel_sdk/group_bulk_write.c
    dynamixel_sdk_c/src/dynamixel_sdk/group_sync_read.c
    dynamixel_sdk_c/src/dynamixel_sdk/group_sync_write.c
    dynamixel_sdk_c/src/dynamixel_sdk/packet_handler.c
    dynamixel_sdk_c/src/dynamixel_sdk/port_handler.c
    dynamixel_sdk_c/src/dynamixel_sdk/protocol1_packet_handler.c
    dynamixel_sdk_c/src/dynamixel_sdk/protocol2_packet_handler.c
    dynamixel_sdk_c/src/dynamixel_sdk/port_handler_linux.c
    )

add_library(dxlsdk SHARED ${dxl_files})

add_executable(XM_class_test.exe src/XM_class_test.cpp src/XM_class.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(XM_class_test.exe dxlsdk ncurses)
