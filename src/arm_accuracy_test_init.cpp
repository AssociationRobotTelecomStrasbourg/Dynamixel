#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Chain(4,1000000);

    if(argc>4)
    {
        uint8_t id2test = atoi(argv[1]);
        std::cout << "Initializing PID..." << std::endl;
        uint16_t P_gain=800;
        uint16_t I_gain=0;
        uint16_t D_gain=0;
        std::cout << "P: " << P_gain << std::endl;
        std::cout << "I: " << I_gain << std::endl;
        std::cout << "D: " << D_gain << std::endl;
        Chain.setParam(id2test,"Position P Gain",P_gain);
        Chain.write();
        Chain.setParam(id2test,"Position I Gain",I_gain);
        Chain.write();
        Chain.setParam(id2test,"Position D Gain",D_gain);
        Chain.write();
        std::cout << "Done" << std::endl;
        std::cout << "Check: " << std::endl;
        Chain.monitorParam(id2test,"Position P Gain");
        Chain.poll();
        Chain.getData(id2test,P_gain);
        Chain.monitorParam(id2test,"Position I Gain");
        Chain.poll();
        Chain.getData(id2test,I_gain);
        Chain.monitorParam(id2test,"Position D Gain");
        Chain.poll();
        Chain.getData(id2test,D_gain);
        std::cout << "P: " << P_gain << std::endl;
        std::cout << "I: " << I_gain << std::endl;
        std::cout << "D: " << D_gain << std::endl;

        std::cout << "Initializing velocity and acceleration profiles...";
        uint32_t pro_vel = 131; // quarter of turn in 1 sec
        uint32_t pro_acc = 17;
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

        int32_t goal_pos[4];
        for(int i=0;i<4;i++)
        {
            goal_pos[i]=atoi(argv[i+2]);
        }
        for(int id=1;id<5;id++)
        {
            Chain.torqueOn(id);
            Chain.setParam(id,"Goal Position",goal_pos[id-1]);
        }
        Chain.write();
    }
    else
    {
        std::cerr << "usage: arm_accuracy_test_init id2test goal_pos1 goal_pos2 goal_pos3 goal_pos4" << std::endl;
    }
}
