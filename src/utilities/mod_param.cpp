#include "XM_class.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <thread>
#include <chrono>

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    uint8_t id=atoi(argv[1]);
    uint8_t new_id=atoi(argv[2]);
    XM Motor(id,1000000);

    bool success=Motor.changeID(new_id);
    if(success)
    {
        std::cout << "Changed ID from " << (unsigned)id << " to " << (unsigned)new_id << std::endl;
    }
    else
    {
        std::cout << "Operation failed" << std::endl;
    }
    return 0;
}
