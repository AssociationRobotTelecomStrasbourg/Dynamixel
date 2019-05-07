#include <iostream>
#include "XM430-W210_Control_Table.h"
#include "XM_bulk_chain.h"
#include "arm_settings.h"

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Arm(4,1000000);

    std::cerr << "Initializing velocity and acceleration profiles...";
    uint32_t pro_vel = PRO_VEL;
    uint32_t pro_acc = PRO_ACC;
    for(int id=1;id<5;id++)
    {
        Arm.setParam(id,"Profile Velocity",pro_vel);
    }
    Arm.write();
    for(int id=1;id<5;id++)
    {
        Arm.setParam(id,"Profile Acceleration",pro_acc);
    }
    Arm.write();
    std::cerr << "Done" << std::endl;

    std::cout << "Initializing PID..." << std::endl;
    for(int id=1;id<5;id++)
    {
        Arm.setParam(id,"Position P Gain",P[id-1]);
    }
    Arm.write();
    for(int id=1;id<5;id++)
    {
        Arm.setParam(id,"Position I Gain",I[id-1]);
    }
    Arm.write();
    for(int id=1;id<5;id++)
    {
        Arm.setParam(id,"Position D Gain",D[id-1]);
    }
    Arm.write();
    std::cout << "Done" << std::endl;

    return 0;
}
