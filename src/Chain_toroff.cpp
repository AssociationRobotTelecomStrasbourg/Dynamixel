#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    if(argc>2)
    {
        uint8_t max_id = atoi(argv[1]);
        int baudrate = atoi(argv[2]);
        XM_bulk_chain Chain(max_id,baudrate);

        std::set<uint8_t> id_list = Chain.getIDlist();
        int n_dxl = id_list.size();
        std::cerr << "Warning: Press ENTER to disable torque on all detected dynamixels" << std::endl;
        std::cin.get();
        for(int id=1;id<(n_dxl+1);id++)
        {
            Chain.torqueOff(id);
        }
    }
    else
    {
        std::cerr << "usage: Chain_toroff max_id baudrate" << std::endl;
    }
    return 0;
}
