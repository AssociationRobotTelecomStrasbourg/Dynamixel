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
    XM_bulk_chain Chain(4,1000000);
    if(argc>1)
    {
        uint8_t id=atoi(argv[1]);
        Chain.reboot(id);
        std::cout << "ID " << (int)id << " rebooted" << std::endl;
    }
    else
    {std::cout << "No ID given" << std::endl;}
    return 0;
}
