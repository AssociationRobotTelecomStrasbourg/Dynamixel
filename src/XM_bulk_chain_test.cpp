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
    uint8_t id=atoi(argv[1]);
    Chain.torqueOff(id);
    uint32_t max_pos_lim=3072;
    Chain.setParam(2,"Max Position Limit",max_pos_lim);
    Chain.write();
    Chain.monitorParam(id,"Current Limit");
    Chain.poll();
    uint16_t cur_lim;
    Chain.getData(id,cur_lim);
    std::cout << "Current Limit : " << (unsigned)cur_lim << std::endl;
    Chain.monitorParam(id,"Min Position Limit");
    Chain.poll();
    uint32_t min_pos_lim;
    Chain.getData(id,min_pos_lim);
    std::cout << "Min Position Limit : " << (unsigned long)min_pos_lim << std::endl;
    Chain.monitorParam(id,"Max Position Limit");
    Chain.poll();
    // uint32_t max_pos_lim;
    Chain.getData(id,max_pos_lim);
    std::cout << "Max Position Limit : " << (unsigned long)max_pos_lim << std::endl;
    return 0;
}
