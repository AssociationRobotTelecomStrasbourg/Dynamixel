#include "XM_class.h"
#include "XM430-W210_Control_Table.h"

extern "C"
{
    #include "dynamixel_sdk.h"
}

extern dxl_control_table XM430_W210_control_table;

#include <iostream>

#define PROTOCOL 2.0

XM::XM(const uint8_t id, const char* port_name, const int baudrate)
{
    //std::cout << "Setting up XM motor on port " << port_name << "..." << std::endl;
    bool op_success = false;
    port_num_ = portHandler(port_name);
    packetHandler();
    op_success = openPort(port_num_);
    if(!op_success)
    {
        std::cerr << "Failed to open port" << std::endl;
    }
    else
    {
        op_success = setBaudRate(port_num_,baudrate);
        if(!op_success)
        {
            std::cerr << "Failed to set baudrate" << std::endl;
        }
        else
        {
            uint16_t addr = XM430_W210_control_table["ID"].address;
            id_ = id;
            write1ByteTxRx(port_num_,PROTOCOL,id_,addr,id);
            std::cout << "Set up XM on " << getPortName(port_num_) << "\n\tBaudrate : " << getBaudRate(port_num_) << "\n\tID : " << (int)read1ByteTxRx(port_num_,PROTOCOL,id_,addr) << std::endl;
        }
    }
}

XM::~XM()
{
    closePort(port_num_);
}

void XM::reset(uint8_t option)
{
    factoryReset(port_num_,PROTOCOL,id_,option);
}

void XM::reboot()
{
    ::reboot(port_num_,PROTOCOL,id_);
}

void XM::ledOn()
{
    uint16_t addr = XM430_W210_control_table["LED"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,1);
}

void XM::ledOff()
{
    uint16_t addr = XM430_W210_control_table["LED"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,0);
}

void XM::torqueOn()
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,1);
}

void XM::torqueOff()
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,0);
}

void XM::setDriveMode(const uint8_t drive_mode)
{
    uint16_t addr = XM430_W210_control_table["Drive Mode"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,drive_mode);
}

void XM::setOperatingMode(const uint8_t operating_mode)
{
    uint16_t addr = XM430_W210_control_table["Operating Mode"].address;
    write1ByteTxRx(port_num_,PROTOCOL,id_,addr,operating_mode);
}

bool XM::setGoalPosition(uint32_t goal_pos)
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    if (read1ByteTxRx(port_num_,PROTOCOL,id_,addr)==1)
    {
        addr = XM430_W210_control_table["Goal Position"].address;
        write4ByteTxRx(port_num_,PROTOCOL,id_,addr,goal_pos);
        return 1;
    }
    else
    {return 0;}
}

bool XM::setGoalVelocity(uint32_t goal_vel)
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    if (read1ByteTxRx(port_num_,PROTOCOL,id_,addr)==1)
    {
        addr = XM430_W210_control_table["Goal Velocity"].address;
        write4ByteTxRx(port_num_,PROTOCOL,id_,addr,goal_vel);
        return 1;
    }
    else
    {return 0;}
}

bool XM::setGoalCurrent(uint32_t goal_cur)
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    if (read1ByteTxRx(port_num_,PROTOCOL,id_,addr)==1)
    {
        addr = XM430_W210_control_table["Goal Current"].address;
        write4ByteTxRx(port_num_,PROTOCOL,id_,addr,goal_cur);
        return 1;
    }
    else
    {return 0;}
}

uint32_t XM::getPresentPosition()
{
    uint16_t addr = XM430_W210_control_table["Present Position"].address;
    uint32_t pres_pos = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_pos;
}

uint32_t XM::getPresentVelocity()
{
    uint16_t addr = XM430_W210_control_table["Present Velocity"].address;
    uint32_t pres_vel = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_vel;
}

uint32_t XM::getPresentCurrent()
{
    uint16_t addr = XM430_W210_control_table["Present Current"].address;
    uint32_t pres_cur = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_cur;
}
