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

    Chain.torqueOff(5);
    // uint8_t op_mode=0;
    // Chain.setParam(5,"Operating Mode",op_mode);
    // Chain.write();
    Chain.monitorParam(5,"Current Limit");
    Chain.poll();
    uint16_t cur_lim;
    Chain.getData(5,cur_lim);
    std::cout << "Current Limit : " << (unsigned)cur_lim << std::endl;
    Chain.monitorParam(5,"Min Position Limit");
    Chain.poll();
    uint32_t min_pos_lim;
    Chain.getData(5,min_pos_lim);
    std::cout << "Min Position Limit : " << (unsigned long)min_pos_lim << std::endl;
    Chain.monitorParam(5,"Max Position Limit");
    Chain.poll();
    uint32_t max_pos_lim;
    Chain.getData(5,max_pos_lim);
    std::cout << "Max Position Limit : " << (unsigned long)max_pos_lim << std::endl;
    return 0;
}
