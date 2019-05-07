#include <iostream>
#include <chrono>
#include "XM430-W210_Control_Table.h"
#include "XM_bulk_chain.h"
#include "arm_settings.h"

extern "C"
{
    #include <wiringPi.h>
    #include <stdlib.h>
}

int main(int argc, char const **argv)
{
    if(argc==6)
    {
        uint32_t pro_vel = PRO_VEL;
        uint32_t pro_acc = PRO_ACC;
        int32_t goal_pos[4];
        uint8_t mov_stat[4];
        int moving;
        std::chrono::steady_clock::time_point t;
        std::chrono::steady_clock::duration time_lapse;
        double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
        double elapsed_time=0;
        int obj_catch = atoi(argv[5]);

        wiringPiSetup();
        pinMode(0,OUTPUT);
        createControlTable();
        XM_bulk_chain Arm(4,1000000);

        std::cerr << "Initializing velocity and acceleration profiles...";

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

        for(int id=1;id<5;id++)
        {
            Arm.monitorParam(id,"Moving Status");
        }

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
        
        // tempo
        t = std::chrono::steady_clock::now();
        do {
            time_lapse = std::chrono::steady_clock::now()-t;
            elapsed_time = time_lapse.count()*time_ratio;
        } while(elapsed_time<0.2);
        
        t = std::chrono::steady_clock::now();
        do {
            Arm.poll();
            for(int id=1;id<5;id++)
            {
                Arm.getData(id,*(mov_stat+(id-1)));
                // std::cerr << id << ": " << std::oct << *(mov_stat+(id-1)) << std::endl;
            }
            moving = !(*mov_stat & 1) && !(*(mov_stat+1) & 1) && !(*(mov_stat+2) & 1) && !(*(mov_stat+3) & 1);
            time_lapse = std::chrono::steady_clock::now()-t;
            // for(int id=1;id<4;id++)
            // {
            //     std::cerr << "Debug: " << id << " Moving Status " << !(*(mov_stat+(id-1)) & 9) << std::endl;
            // }
            elapsed_time = time_lapse.count()*time_ratio;
        } while(moving && (elapsed_time<3.0));
        digitalWrite(0,obj_catch);
    }
    else
    {
        std::cerr << "Wrong arguments given. Expected 4 integers and 1 or 0" << std::endl;
    }
    return 0;
}
