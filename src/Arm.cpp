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

    for(int id=1;id<6;id++)
    {
        Chain.torqueOn(id);
    }

    int32_t goal_pos[]={2048,2048,2048,2048,2500};
    for(int id=1;id<6;id++)
    {
        Chain.setParam(id,"Goal Position",*(goal_pos+(id-1)));
    }
    Chain.write();

    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Present Position");
    }
    int32_t pos[5];
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,*(pos+(id-1)));
        std::cout << "[ID " << id << "]" << "Present pos : " << (long)*(pos+(id-1)) << std::endl;
    }
    return 0;
}
