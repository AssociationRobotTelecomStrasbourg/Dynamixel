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
    
    Chain.torqueOn(5);
    int32_t goal_pos=2500;
    Chain.setParam(5,"Goal Position",goal_pos);
    Chain.write();
    Chain.monitorParam(5,"Present Position");
    Chain.poll();
    int32_t pos;
    Chain.getData(5,pos);
    std::cout << "Present pos : " << (long)pos << std::endl;
    return 0;
}
