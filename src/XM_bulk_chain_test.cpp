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
    uint8_t op_mode=0;
    Chain.setParam(5,"Operating Mode",op_mode);
    Chain.write();
    Chain.monitorParam(5,"Operating Mode");
    Chain.poll();
    uint8_t op_mode_check;
    Chain.getData(5,op_mode_check);
    std::cout << "Operating Mode : " << (long)op_mode_check << std::endl;
    return 0;
}
