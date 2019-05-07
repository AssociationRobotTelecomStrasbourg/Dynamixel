cmake_minimum_required(VERSION 2.8.3)

project(ARTS_Dynamixel)

find_package(Threads REQUIRED)

include_directories(include dynamixel_sdk_c/include/dynamixel_sdk)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../..)

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

# utilities
add_executable(Chain_reboot.exe src/utilities/Chain_reboot.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_reboot.exe dxlsdk)

add_executable(Chain_toroff.exe src/utilities/Chain_toroff.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_toroff.exe dxlsdk)

add_executable(mod_param.exe src/utilities/mod_param.cpp src/classes/XM_class.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(mod_param.exe dxlsdk)

add_executable(id.exe src/utilities/XM_model_identification.cpp src/classes/XM_class.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(id.exe dxlsdk)
set_target_properties(id.exe PROPERTIES OUTPUT_NAME identification)

add_executable(Chain_change_baud.exe src/utilities/XM_bulk_chain_change_baudrate.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(Chain_change_baud.exe dxlsdk)

add_executable(XM_bulk_chain_monitor.exe src/utilities/XM_bulk_chain_monitor.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(XM_bulk_chain_monitor.exe dxlsdk)

# demo
# gripper
add_executable(arm_demo_save.exe src/arm/demo/gripper/arm_demo_save.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_demo_save.exe dxlsdk)

add_executable(arm_demo_load.exe src/arm/demo/gripper/arm_demo_load.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_demo_load.exe dxlsdk)

# pen
add_executable(learn2write.exe src/arm/demo/pen/learn2write.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(learn2write.exe dxlsdk ${CMAKE_THREAD_LIBS_INIT})

# arm
add_executable(arm_gotopos.exe src/arm/arm_gotopos.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_gotopos.exe dxlsdk)

add_executable(arm_init.exe src/arm/arm_init.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_init.exe dxlsdk)

# Raspberry PI only
add_executable(arm_pump_control.exe src/arm/pi/arm_pump_control.cpp src/classes/XM_bulk_chain.cpp src/classes/XM430-W210_Control_Table.cpp)
target_link_libraries(arm_pump_control.exe dxlsdk wiringPi)

