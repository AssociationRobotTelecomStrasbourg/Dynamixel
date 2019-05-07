#include <iostream>
#include "XM430-W210_Control_Table.h"
#include "XM_bulk_chain.h"
#include "arm_settings.h"

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char const **argv)
{
    if(argc==5)
    {
        createControlTable();
        XM_bulk_chain Arm(4,1000000);

        std::cerr << "Initializing velocity and acceleration profiles...";
        uint32_t pro_vel = PRO_VEL; // quarter of turn in 1 sec
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

        int32_t goal_pos[4];

        for (int i = 0; i < 4; i++)
        {
            *(goal_pos+i) = atoi(argv[i+1]);
            std::cerr << *(goal_pos+i) << std::endl;
        }
        for (uint8_t id = 1; id < 5; id++)
        {
            Arm.torqueOn(id);
            Arm.setParam(id,"Goal Position",goal_pos[id-1]);
        }
        Arm.write();
    }
    else
    {
        std::cerr << "Wrong arguments given. Expected 4 integers" << std::endl;
    }
    return 0;
}
