#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>

extern "C"
{
    #include <ncurses.h>
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

    int32_t goal_pos[]={2000,2000,2100,2000,2048};
    for(int id=1;id<6;id++)
    {
        Chain.setParam(id,"Goal Position",*(goal_pos+id));
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
        Chain.getData(id,*(pos+id));
        std::cout << "[ID " << id << "]" << "Present pos : " << (long)*(pos+id) << std::endl;
    }
    return 0;
}
