#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char** argv)
{
    if(argc>2)
    {
        int baudrate = atoi(argv[2]);
        createControlTable();
        XM_bulk_chain Chain(8,baudrate);

        uint8_t id=atoi(argv[1]);

        Chain.reboot(id);
        std::cerr << "ID " << (int)id << " rebooted" << std::endl;
    }
    else
    {std::cerr << "usage: Chain_reboot id baudrate" << std::endl;}
    return 0;
}
