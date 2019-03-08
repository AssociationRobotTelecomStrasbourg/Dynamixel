#include "XM_class.h"
#include "XM430-W210_Control_Table.h"

extern "C"
{
    #include "dynamixel_sdk.h"
}

extern dxl_control_table XM430_W210_control_table;

#include <iostream>

#define PROTOCOL 2.0

XM::XM(const uint8_t id, const int baudrate, const char* port_name)
{
    //std::cerr << "Setting up XM motor on port " << port_name << "..." << std::endl;
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
            std::cerr << "Set up XM on " << getPortName(port_num_) << "\n\tBaudrate : " << getBaudRate(port_num_) << "\n\tID : " << (int)read1ByteTxRx(port_num_,PROTOCOL,id_,addr) << std::endl;
        }
    }
}

XM::~XM()
{
    std::cerr << "Deleting XM object...";
    clearPort(port_num_);
    closePort(port_num_);
    std::cerr << "Done" << std::endl;
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

bool XM::setGoalPosition(int32_t goal_pos)
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

bool XM::setGoalVelocity(int32_t goal_vel)
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

bool XM::setGoalCurrent(int16_t goal_cur)
{
    uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
    if (read1ByteTxRx(port_num_,PROTOCOL,id_,addr)==1)
    {
        addr = XM430_W210_control_table["Goal Current"].address;
        write2ByteTxRx(port_num_,PROTOCOL,id_,addr,goal_cur);
        return 1;
    }
    else
    {return 0;}
}

int32_t XM::getPresentPosition()
{
    uint16_t addr = XM430_W210_control_table["Present Position"].address;
    int32_t pres_pos = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_pos;
}

int32_t XM::getPresentVelocity()
{
    uint16_t addr = XM430_W210_control_table["Present Velocity"].address;
    int32_t pres_vel = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_vel;
}

int16_t XM::getPresentCurrent()
{
    uint16_t addr = XM430_W210_control_table["Present Current"].address;
    int16_t pres_cur = read2ByteTxRx(port_num_,PROTOCOL,id_,addr);
    return pres_cur;
}

bool XM::generic_write(const char* paramName, uint8_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==0)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write1ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_write(const char* paramName, int8_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==1)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write1ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_write(const char* paramName, uint16_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==2)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write2ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_write(const char* paramName, int16_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==3)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write2ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_write(const char* paramName, uint32_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==4)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write4ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_write(const char* paramName, int32_t paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==5)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            write4ByteTxRx(port_num_,PROTOCOL,id_,addr,paramValue);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}


bool XM::generic_read(const char* paramName, uint8_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==0)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read1ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_read(const char* paramName, int8_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==1)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read1ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_read(const char* paramName, uint16_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==2)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read2ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_read(const char* paramName, int16_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==3)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read2ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_read(const char* paramName, uint32_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==4)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}

bool XM::generic_read(const char* paramName, int32_t& paramValue)
{
    if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
    {
        if(XM430_W210_control_table[paramName].data_type==5)
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            paramValue = read4ByteTxRx(port_num_,PROTOCOL,id_,addr);
            return 1;
        }
        else
        {
            std::cerr << "Error : Wrong data type for given param" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Error : Invalid parameter name" << std::endl;
        return 0;
    }
}
