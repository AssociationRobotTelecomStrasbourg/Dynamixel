#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Chain(4,1000000);

    std::cout << "Initializing profiles as time-based...";
    uint8_t drive_mode = 4;
    for(int id=1;id<4;id++)
    {
        Chain.setParam(id,"Drive Mode",drive_mode);
    }
    Chain.write();
    std::cout << "Done" << std::endl;

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

    // uint8_t op_mode[4];
    // for(int id=1;id<5;id++)
    // {
    //     Chain.monitorParam(id,"Operating Mode");
    // }
    // Chain.poll();
    // for(int id=1;id<5;id++)
    // {
    //     Chain.getData(id,*(op_mode+(id-1)));
    //     std::cout << "Debug: Operating mode " << id << ": " << (unsigned)*(op_mode+(id-1)) << std::endl;
    // }

    // std::cout << "Initializing PID...";
    // uint16_t P_gains[5]={10000,10000,10000,10000,10000};
    // uint16_t I_gains[5]={1000,1000,1000,1000,1000};
    // uint16_t D_gains[5]={100,500,500,500,500};
    // for(int id=1;id<6;id++)
    // {
    //     Chain.setParam(id,"Position P Gain",P_gains[id-1]);
    // }
    // Chain.write();
    // for(int id=1;id<6;id++)
    // {
    //     Chain.setParam(id,"Position I Gain",I_gains[id-1]);
    // }
    // Chain.write();
    // for(int id=1;id<6;id++)
    // {
    //     Chain.setParam(id,"Position D Gain",D_gains[id-1]);
    // }
    // Chain.write();
    // std::cout << "Done" << std::endl;

    for(int id=1;id<4;id++)
    {
        Chain.monitorParam(id,"Moving Status");
    }

    char* fname;
    if(argc>1)
    {fname = argv[1];}
    else
    {fname="demo.txt";}

    std::ifstream infile(fname);

    int32_t pos[] = {0,0,0};
    int16_t cur = 0;

    int nb_poses = 0;
    uint8_t mov_stat[3];
    int moving;

    std::chrono::steady_clock::time_point t;
    std::chrono::steady_clock::duration time_lapse;
    double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    double elapsed_time=0;

    infile >> nb_poses;
    if(nb_poses!=0)
    {
        std::cout << nb_poses << " poses loaded. Press any key to launch demo" << std::endl;
        std::cin.get();
        for(int id=1;id<5;id++)
        {
            Chain.torqueOn(id);
        }
        for(int i=1;i<(nb_poses+1);i++)
        {
            t = std::chrono::steady_clock::now();
            std::cout << "Pose : "<< i << "/" << nb_poses << std::endl;
            for(int id=1;id<4;id++)
            {
                infile >> *(pos+(id-1));
                std::cout << *(pos+(id-1)) << "\t";
                Chain.setParam(id,"Goal Position",*(pos+(id-1)));
            }
            infile >> cur;
            std::cout << cur << "\t" << std::endl;
            Chain.setParam(4,"Goal Current",cur);
            Chain.write();
            if(cur<0)
            {
                cur=0;
                Chain.setParam(4,"Goal Current",cur);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                Chain.write();
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            do {
                Chain.poll();
                for(int id=1;id<4;id++)
                {
                    Chain.getData(id,*(mov_stat+(id-1)));
                }
                moving = !(*mov_stat & 9) || !(*(mov_stat+1) & 9) || !(*(mov_stat+2) & 9);
                time_lapse = std::chrono::steady_clock::now()-t;
                // for(int id=1;id<4;id++)
                // {
                //     std::cerr << "Debug: " << id << " Moving Status " << !(*(mov_stat+(id-1)) & 9) << std::endl;
                // }
                elapsed_time = time_lapse.count()*time_ratio;
            } while(moving && (elapsed_time<3.0));
        }
        std::cout << "Please secure the arm (stabilize it or prepare to catch it). Press any key to confirm" << std::endl;
        std::cin.get();
        for(int id=1;id<5;id++)
        {
            Chain.torqueOff(id);
        }
    }
    else
    {
        std::cerr << "No positions loaded" << std::endl;
    }
    return 0;
}
