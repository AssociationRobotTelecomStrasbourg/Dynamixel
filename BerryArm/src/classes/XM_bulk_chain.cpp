#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"

extern "C"
{
    #include "dynamixel_sdk.h"
}

extern dxl_control_table XM430_W210_control_table;

#include <iostream>

#define PROTOCOL 2.0

XM_bulk_chain::XM_bulk_chain(uint8_t max_id, const int baudrate, const char* port_name)
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
            broadcastPing(port_num_,PROTOCOL);
            for (int id = 0; id < (max_id+1); id++)
            {
                if(getBroadcastPingResult(port_num_, PROTOCOL, id))
                {
                    id_list_.insert(id);
                }
  	        }
            std::cerr << "Set up XM Chain on " << getPortName(port_num_) << " with baudrate " << getBaudRate(port_num_);
            std::cerr << "\nIDs : " << std::endl;
            for(std::set<uint8_t>::iterator i=id_list_.begin(); i!=id_list_.end(); ++i)
            {
                std::cerr << "\t" << (int)*i << std::endl;
            }
        }
    }
}

XM_bulk_chain::~XM_bulk_chain()
{
    std::cerr << "Deleting XM Bulk Chain object...";
    clearPort(port_num_);
    closePort(port_num_);
    std::cerr << "Done" << std::endl;
}

std::set<uint8_t> XM_bulk_chain::getIDlist()
{
    std::set<uint8_t> id_list = id_list_;
    return(id_list);
}

void XM_bulk_chain::reboot(uint8_t id)
{
    if(id_list_.find(id)!=id_list_.end())
        ::reboot(port_num_,PROTOCOL,id);
    else
        std::cerr << "Can't reboot : ID not in list" << std::endl;
}

void XM_bulk_chain::ledOn(uint8_t id)
{
    if(id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["LED"].address;
        write1ByteTxRx(port_num_, PROTOCOL,id,addr,1);
    }
    else
        std::cerr << "Can't enable LED : ID not in list" << std::endl;
}

void XM_bulk_chain::ledOff(uint8_t id)
{
    if(id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["LED"].address;
        write1ByteTxRx(port_num_, PROTOCOL,id,addr,0);
    }
    else
        std::cerr << "Can't disable LED : ID not in list" << std::endl;
}

void XM_bulk_chain::torqueOn(uint8_t id)
{
    if(id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
        write1ByteTxRx(port_num_, PROTOCOL,id,addr,1);
    }
    else
        std::cerr << "Can't enable torque : ID not in list" << std::endl;
}

void XM_bulk_chain::torqueOff(uint8_t id)
{
    if(id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["Torque Enable"].address;
        write1ByteTxRx(port_num_, PROTOCOL,id,addr,0);
    }
    else
        std::cerr << "Can't disable torque : ID not in list" << std::endl;
}

void XM_bulk_chain::setDriveMode(uint8_t id, const uint8_t drive_mode)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["Drive Mode"].address;
        write1ByteTxRx(port_num_,PROTOCOL,id,addr,drive_mode);
    }
    else
    {
        std::cerr << "Can't set drive mode : ID not in list" << std::endl;
    }
}
void XM_bulk_chain::setOperatingMode(uint8_t id, const uint8_t operating_mode)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        uint16_t addr = XM430_W210_control_table["Operating Mode"].address;
        write1ByteTxRx(port_num_,PROTOCOL,id,addr,operating_mode);
    }
    else
    {
        std::cerr << "Can't set drive mode : ID not in list" << std::endl;
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const uint8_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==0)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const int8_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==1)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const uint16_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==2)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const int16_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==3)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const uint32_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==4)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::setParam(uint8_t id, const char* paramName, const int32_t paramValue)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t data_type = XM430_W210_control_table[paramName].data_type;
            uint8_t size = XM430_W210_control_table[paramName].size;
            if(data_type==5)
            {
                bool success=groupBulkWriteAddParam(groupread_num_,id,addr,size,paramValue,size);
                return(success);
            }
            else
            {
                std::cerr << "Can't add param to write list : Invalid param data_type" << std::endl;
                return(false);
            }
        }
        else
        {
            std::cerr << "Can't add param to write list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to write list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::write()
{
    groupBulkWriteTxPacket(groupwrite_num_);
    int dxl_comm_result = getLastTxRxResult(port_num_, PROTOCOL);
    if (dxl_comm_result!=0)
    {
        std::cerr << "TxRx Error : " << getTxRxResult(PROTOCOL,dxl_comm_result) << std::endl;
        groupBulkWriteClearParam(groupwrite_num_);
        return(false);
    }
    else
    {
        groupBulkWriteClearParam(groupwrite_num_);
        return(true);
    }
}

bool XM_bulk_chain::monitorParam(uint8_t id, const char* paramName)
{
    if (id_list_.find(id)!=id_list_.end())
    {
        bool success = false;
        if(XM430_W210_control_table.find(paramName)!=XM430_W210_control_table.end())
        {
            if(param_monitor_list_.find(id)!=param_monitor_list_.end())
            {groupBulkReadRemoveParam(groupread_num_,id);}
            uint16_t addr = XM430_W210_control_table[paramName].address;
            uint8_t length = XM430_W210_control_table[paramName].size;
            success=groupBulkReadAddParam(groupread_num_,id,addr,length);
            param_monitor_list_[id] = paramName;
            return(success);
        }
        else
        {
            std::cerr << "Can't add param to monitor list : Invalid param name" << std::endl;
            return(false);
        }
    }
    else
    {
        std::cerr << "Can't add param to monitor list : ID not in list" << std::endl;
        return(false);
    }
}

bool XM_bulk_chain::poll()
{
    groupBulkReadTxRxPacket(groupread_num_);
    int dxl_comm_result = getLastTxRxResult(port_num_, PROTOCOL);
    if (dxl_comm_result!=0)
    {
        std::cerr << "TxRx Error : " << getTxRxResult(PROTOCOL,dxl_comm_result) << std::endl;
        return(false);
    }
    else
    {
        return(true);
    }
}

void XM_bulk_chain::getData(uint8_t id, uint8_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}

void XM_bulk_chain::getData(uint8_t id, int8_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}

void XM_bulk_chain::getData(uint8_t id, uint16_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}

void XM_bulk_chain::getData(uint8_t id, int16_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}

void XM_bulk_chain::getData(uint8_t id, uint32_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}

void XM_bulk_chain::getData(uint8_t id, int32_t& d)
{
    if(param_monitor_list_.find(id)!=param_monitor_list_.end())
    {
        if(groupBulkReadIsAvailable(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size))
        {
            d = groupBulkReadGetData(groupread_num_,id,XM430_W210_control_table[param_monitor_list_[id]].address,XM430_W210_control_table[param_monitor_list_[id]].size);
        }
        else
        {
            std::cerr << "Get data failed for ID : " << (int)id << std::endl;
        }
    }
    else
    {
        std::cerr << "No parameter is set for monitoring for given ID : " << (int)id << std::endl;
    }
}
