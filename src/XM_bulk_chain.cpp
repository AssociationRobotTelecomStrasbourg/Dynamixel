#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"

extern "C"
{
    #include "dynamixel_sdk.h"
}

extern dxl_control_table XM430_W210_control_table;

#include <iostream>

#define PROTOCOL 2.0

XM_bulk_chain::XM_bulk_chain(const char* port_name="/dev/ttyUSB0", const int baudrate=57600)
{
    port_num_ = portHandler(port_name);
    packetHandler();
    groupwrite_num_ = groupBulkWrite(port_num_,PROTOCOL);
    groupread_num_ = groupBulkRead(port_num_,PROTOCOL);
    if(!openPort(port_num_))
    {std::cerr << "Failed to open port" << std::endl;}
    else
    {
        if(!setBaudRate(port_num_,baudrate))
        {std::cerr << "Failed to set baudrate" << std::endl;}
        else
        {
            for (id = 1; id < 253; id++)
            {
  	             dxl_model_num = pingGetModelNum(port_num_, PROTOCOL, id);
                 if (getLastTxRxResult(port_num_, PROTOCOL) == COMM_SUCCESS)
  	{
      fprintf(stderr, "\n                                          ... SUCCESS \r");
      fprintf(stderr, " [ID:%.3d] Model No : %.5d \n", id, dxl_model_num);
    }
        }
    }
}

XM_bulk_chain::~XM_bulk_chain()

void XM_bulk_chain::reset(uint8_t id)
void XM_bulk_chain::reboot(uint8_t id)

void XM_bulk_chain::ledOn(uint8_t id)
void XM_bulk_chain::ledOff(uint8_t id)

void XM_bulk_chain::torqueOn(uint8_t id)
void XM_bulk_chain::torqueOff(uint8_t id)

void XM_bulk_chain::setDriveMode(uint8_t id, const uint8_t drive_mode)
void XM_bulk_chain::setOperatingMode(uint8_t id, const uint8_t operating_mode)

bool XM_bulk_chain::setGoalPosition(uint8_t id, uint32_t goal_pos)
bool XM_bulk_chain::setGoalVelocity(uint8_t id, uint32_t goal_vel)
bool XM_bulk_chain::setGoalCurrent(uint8_t id, uint32_t goal_cur)

bool XM_bulk_chain::monitorParam(uint8_t id, const char* paramName)
