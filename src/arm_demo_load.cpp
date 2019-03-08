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
    XM_bulk_chain Chain(5,1000000);

    std::cout << "Initializing velocity and acceleration profiles...";
    uint32_t pro_vel = 131; //180° rotation in 1 s
    uint32_t pro_acc = pro_vel/2;
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

    uint8_t op_mode[5];
    for(int id=1;id<6;id++)
    {
        Chain.monitorParam(id,"Operating Mode");
    }
    Chain.poll();
    for(int id=1;id<6;id++)
    {
        Chain.getData(id,*(op_mode+(id-1)));
        std::cout << "Debug: Operating mode " << id << ": " << (unsigned)*(op_mode+(id-1)) << std::endl;
    }

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

    for(int id=1;id<5;id++)
    {
        Chain.monitorParam(id,"Moving Status");
    }

    char* fname;
    if(argc>1)
    {fname = argv[1];}
    else
    {fname="demo.txt";}

    std::ifstream infile(fname);

    int32_t pos[] = {0,0,0,0};
    int16_t cur = 0;

    int nb_poses = 0;
    uint8_t mov_stat[5];
    int moving;

    infile >> nb_poses;
    if(nb_poses!=0)
    {
        std::cout << nb_poses << " poses loaded. Press any key to launch demo" << std::endl;
        std::cin.get();
        for(int id=1;id<6;id++)
        {
            Chain.torqueOn(id);
        }
        for(int i=1;i<(nb_poses+1);i++)
        {
            std::cout << "Pose : "<< i << "/" << nb_poses << std::endl;
            for(int id=1;id<5;id++)
            {
                infile >> *(pos+(id-1));
                std::cout << *(pos+(id-1)) << "\t";
                Chain.setParam(id,"Goal Position",*(pos+(id-1)));
            }
            infile >> cur;
            std::cout << cur << "\t" << std::endl;
            Chain.setParam(5,"Goal Current",cur);
            Chain.write();
            do {
                Chain.poll();
                for(int id=1;id<5;id++)
                {
                    Chain.getData(id,*(mov_stat+(id-1)));
                }
                moving = (!(*mov_stat & 00000001) && (!(*mov_stat & 0001000))) || (!(*(mov_stat+1) & 00000001) && (!(*(mov_stat+1) & 0001000))) || (!(*(mov_stat+2) & 00000001) && (!(*(mov_stat+2) & 0001000))) || (!(*(mov_stat+3) & 00000001) && (!(*(mov_stat+3) & 0001000))) || (!(*(mov_stat+4) & 00000001) && (!(*(mov_stat+4) & 0001000)));
            } while(moving);
        }
        std::cout << "Please secure the arm (stabilize it or prepare to catch it). Press any key to confirm" << std::endl;
        std::cin.get();
        for(int id=1;id<6;id++)
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
