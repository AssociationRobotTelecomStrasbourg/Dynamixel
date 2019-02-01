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
    XM_bulk_chain Chain;

    std::set<uint8_t> id_list = Chain.getIDlist();
    int n_dxl = id_list.size();

    for(int id=1;id<(n_dxl+1);id++)
    {
        Chain.torqueOff(id);
    }
    return 0;
}
