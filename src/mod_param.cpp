#include "XM_bulk_chain.h"
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
    XM_bulk_chain Chain(5);


    uint32_t pro_vel_cur;
    uint32_t pro_acc_cur;
    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Profile Velocity");
    }
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,pro_vel_cur);
        std::cout << "[ID " << id << "]" << "Profile velocity : " << (unsigned long)pro_vel_cur << std::endl;
    }

    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Profile Acceleration");
    }
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,pro_acc_cur);
        std::cout << "[ID " << id << "]" << "Profile acceleration : " << (unsigned long)pro_acc_cur << std::endl;
    }
    std::cout << "Writing...";

    uint32_t pro_vel = strtoul(argv[1],NULL,0);
    uint32_t pro_acc = strtoul(argv[2],NULL,0);
    for(int id=1;id<5;id++)
    {
        Chain.setParam(id,"Profile Velocity",pro_vel);
    }
    Chain.write();
    for(int id=1;id<5;id++)
    {
        Chain.setParam(id,"Profile Acceleration",pro_acc);
    }
    Chain.write();
    std::cout << "Done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Profile Velocity");
    }
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,pro_vel_cur);
        std::cout << "[ID " << id << "]" << "Profile velocity : " << (unsigned long)pro_vel_cur << std::endl;
    }

    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Profile Acceleration");
    }
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,pro_acc_cur);
        std::cout << "[ID " << id << "]" << "Profile acceleration : " << (unsigned long)pro_acc_cur << std::endl;
    }

    return 0;
}
