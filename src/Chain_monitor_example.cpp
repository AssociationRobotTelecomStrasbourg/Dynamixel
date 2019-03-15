#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <thread>
#include <chrono>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Chain(4,1000000);

    for(int id=1;id<4;id++)
    {
        Chain.torqueOff(id);
    }

    std::cout << "Initializing velocity and acceleration profiles...";
    uint32_t pro_vel = 131; // quarter of turn in 1 sec
    uint32_t pro_acc = 17;
    for(int id=1;id<4;id++)
    {
        Chain.setParam(id,"Profile Velocity",pro_vel);
    }
    Chain.write();
    for(int id=1;id<4;id++)
    {
        Chain.setParam(id,"Profile Acceleration",pro_acc);
    }
    Chain.write();
    std::cout << "Done" << std::endl;

    for(int id=1;id<5;id++)
    {
        Chain.monitorParam(id,"Present Position");
    }
    int32_t pos[4];
    Chain.poll();
    for(int id=1;id<5;id++)
    {
        Chain.getData(id,*(pos+(id-1)));
        std::cout << "[ID " << id << "]" << "Present pos : " << (long)*(pos+(id-1)) << std::endl;
    }

    std::cout << "Prepare yourself, THE arm is coming..." << std::endl;
    std::cin.get();

    int32_t goal_pos=2000;
    for(int id=1;id<4;id++)
    {
        Chain.torqueOn(id);
        std::cout << id << " " << Chain.setParam(id,"Goal Position",goal_pos) << std::endl;
    }
    // Chain.setParam(2,"Goal Position",goal_pos);
    Chain.write();
    // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    // goal_pos=1024;
    // Chain.setParam(2,"Goal Position",goal_pos);
    // Chain.write();
    std::cout << "Not..." << std::endl;
    Chain.poll();
    for(int id=1;id<4;id++)
    {
        Chain.getData(id,*(pos+(id-1)));
        std::cout << "[ID " << id << "]" << "Present pos : " << (long)*(pos+(id-1)) << std::endl;
    }

    std::cout << "Prepare yourself, THE arm is falling...";
    std::cin.get();
    for(int id=1;id<4;id++)
    {
        Chain.torqueOff(id);
    }
    std::cout << "Now" << std::endl;
    return 0;
}
