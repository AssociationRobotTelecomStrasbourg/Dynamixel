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

add_executable(XM_bulk_chain_test.exe src/XM_bulk_chain_test.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(XM_bulk_chain_test.exe dxlsdk)

add_executable(Chain_reboot.exe src/Chain_reboot.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_reboot.exe dxlsdk)

add_executable(Chain_monitor_example.exe src/Chain_monitor_example.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_monitor_example.exe dxlsdk)

add_executable(Chain_toroff.exe src/Chain_toroff.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_toroff.exe dxlsdk)

add_executable(arm_demo_save.exe src/arm_demo_save.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_demo_save.exe dxlsdk ncurses)

add_executable(mod_param.exe src/mod_param.cpp src/XM_class.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(mod_param.exe dxlsdk)

add_executable(arm_demo_load.exe src/arm_demo_load.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_demo_load.exe dxlsdk)

add_executable(id.exe src/XM_model_identification.cpp src/XM_class.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(id.exe dxlsdk)
set_target_properties(id.exe PROPERTIES OUTPUT_NAME identification)

add_executable(Chain_change_baud.exe src/XM_bulk_chain_change_baudrate.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_change_baud.exe dxlsdk)

add_executable(XM_bulk_chain_monitor.exe src/XM_bulk_chain_monitor.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(XM_bulk_chain_monitor.exe dxlsdk ncurses)

add_executable(arm_accuracy_test.exe src/arm_accuracy_test.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_accuracy_test.exe dxlsdk)

add_executable(arm_accuracy_test_init.exe src/arm_accuracy_test_init.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_accuracy_test_init.exe dxlsdk)

add_executable(arm_gotopos.exe src/arm_gotopos.cpp src/XM_bulk_chain.cpp src/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_gotopos.exe dxlsdk)
