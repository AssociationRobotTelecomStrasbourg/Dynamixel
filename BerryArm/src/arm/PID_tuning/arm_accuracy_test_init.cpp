#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include "arm_settings.h"
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

    if(argc==5)
    {
        for(int id=1;id<5;id++)
        {
            Chain.torqueOn(id);
        }

        std::cout << "Initializing velocity and acceleration profiles...";
        uint32_t pro_vel = 500;
        uint32_t pro_acc = 500/3;
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

        uint8_t id2test = atoi(argv[1]);

        std::cout << "Initializing PID..." << std::endl;
        uint16_t P_gain=atoi(argv[2]);
        uint16_t I_gain=atoi(argv[3]);
        uint16_t D_gain=atoi(argv[4]);
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
    }
    else
    {
        std::cerr << "usage: arm_accuracy_test_init.exe id2test P I D" << std::endl;
    }
}
