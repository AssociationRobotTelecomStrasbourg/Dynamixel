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

typedef std::unordered_map<std::string,std::string> control_table_values;

int main(int argc, char** argv)
{
    createControlTable();
    control_table_values ctv_tab;
    XM_bulk_chain Chain(5,1000000);
    void* data;
    char data_str[30];
    std::string data_str_ffs;
    const char* paramName;
    if(argc==2)
    {
        while(true)
        {
            int id = atoi(argv[1]);
            for(auto it = XM430_W210_control_table.begin(); it!=XM430_W210_control_table.end();++it)
            {
                // std::cerr << "Debug: " << (*it).first << std::endl;
                paramName = ((*it).first).c_str();

                Chain.monitorParam(id,paramName);

                Chain.poll();
                switch (XM430_W210_control_table[(*it).first].data_type)
                {
                    case 0:
                        // std::cerr << "Debug: uint8_t"<< std::endl;
                        data = malloc(sizeof(uint8_t));
                        Chain.getData(id,*static_cast<uint8_t*>(data));
                        sprintf(data_str,"%u",*static_cast<uint8_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    case 1:
                        // std::cerr << "Debug: int8_t"<< std::endl;
                        data = malloc(sizeof(int8_t));
                        Chain.getData(id,*static_cast<int8_t*>(data));
                        sprintf(data_str,"%d",*static_cast<int8_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    case 2:
                        // std::cerr << "Debug: uint16_t"<< std::endl;
                        data = malloc(sizeof(uint16_t));
                        Chain.getData(id,*static_cast<uint16_t*>(data));
                        sprintf(data_str,"%u",*static_cast<uint16_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    case 3:
                        // std::cerr << "Debug: int16_t"<< std::endl;
                        data = malloc(sizeof(int16_t));
                        Chain.getData(id,*static_cast<int16_t*>(data));
                        sprintf(data_str,"%d",*static_cast<int16_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    case 4:
                        // std::cerr << "Debug: uint32_t"<< std::endl;
                        data = malloc(sizeof(uint32_t));
                        Chain.getData(id,*static_cast<uint32_t*>(data));
                        sprintf(data_str,"%u",*static_cast<uint32_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    case 5:
                        // std::cerr << "Debug: int32_t"<< std::endl;
                        data = malloc(sizeof(int32_t));
                        Chain.getData(id,*static_cast<int32_t*>(data));
                        sprintf(data_str,"%d",*static_cast<int32_t*>(data));
                        data_str_ffs = data_str;
                        ctv_tab[(*it).first] = data_str_ffs;
                        free(data);
                        break;
                    default :
                        break;
                }
            }
            for(auto iter=ctv_tab.begin();iter!=ctv_tab.end();++iter)
            {
                std::cerr << (*iter).first << ": " << (*iter).second << std::endl;
            }
            std::cerr << "Press ENTER to refresh" << std::endl;
            std::cin.get();
        }
    }
    else
    {
        std::cerr << "usage: XM_bulk_chain_monitor.exe id" << std::endl;
    }
    return 0;
}
