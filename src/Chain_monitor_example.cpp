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
        Chain.monitorParam(id,"Present Position");
    }
    int32_t pos[5];
    Chain.poll();
    for(int id=1;id<(n_dxl+1);id++)
    {
        Chain.getData(id,*(pos+(id-1)));
        std::cout << "[ID " << id << "]" << "Present pos : " << (long)*(pos+(id-1)) << std::endl;
    }
    return 0;
}
