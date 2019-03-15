#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>

extern "C"
{
    #include <stdlib.h>
}

extern dxl_control_table XM430_W210_control_table;

typedef std::unordered_map<std::string,const char*> control_table_values;

int main(int argc, char** argv)
{
    createControlTable();
    control_table_values ctv_tab;
    XM_bulk_chain Chain(5,1000000);
    void* data;
    char data_str[30];
    const char* paramName;
    uint8_t id = atoi(argv[1]);
    while(true)
    {
        for(auto it = XM430_W210_control_table.begin(); it!=XM430_W210_control_table.end();++it)
        {
            std::cerr << "Debug: " << (*it).first << std::endl;
            paramName = ((*it).first).c_str();
            for(int id=1;id<6;id++)
            {
                Chain.monitorParam(id,paramName);
            }
            Chain.poll();
            switch (XM430_W210_control_table[(*it).first].data_type)
            {
                case 0:
                    std::cerr << "Debug: uint8_t"<< std::endl;
                    Chain.getData(id,*static_cast<uint8_t*>(data));
                    sprintf(data_str,"%u",*static_cast<uint8_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                case 1:
                    std::cerr << "Debug: int8_t"<< std::endl;
                    Chain.getData(id,*static_cast<int8_t*>(data));
                    sprintf(data_str,"%d",*static_cast<int8_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                case 2:
                    std::cerr << "Debug: uint16_t"<< std::endl;
                    Chain.getData(id,*static_cast<uint16_t*>(data));
                    sprintf(data_str,"%u",*static_cast<uint16_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                case 3:
                    std::cerr << "Debug: int16_t"<< std::endl;
                    Chain.getData(id,*static_cast<int16_t*>(data));
                    sprintf(data_str,"%d",*static_cast<int16_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                case 4:
                    std::cerr << "Debug: uint32_t"<< std::endl;
                    Chain.getData(id,*static_cast<uint32_t*>(data));
                    sprintf(data_str,"%u",*static_cast<uint32_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                case 5:
                    std::cerr << "Debug: int32_t"<< std::endl;
                    Chain.getData(id,*static_cast<int32_t*>(data));
                    sprintf(data_str,"%d",*static_cast<int32_t*>(data));
                    ctv_tab[(*it).first]=data_str;
                    break;
                default :
                    break;
            }
        }
        std::cerr << "ID: " << (unsigned)id << std::endl;
        for(auto iter=ctv_tab.begin();iter!=ctv_tab.end();++iter)
        {
            std::cerr << (*iter).first << ": " << (*iter).second << std::endl;
        }
        std::cerr << "Press any key to refresh" << std::endl;
        std::cin.get();
    }
    return 0;
}
