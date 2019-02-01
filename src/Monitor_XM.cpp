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

    if(argc>1)
    {
        int id = atoi(argv[1]);

        return 0;
    }
    else
    {
        std::cerr << "Set ID to monitor" << std::endl;
        return -1;
    }
}
