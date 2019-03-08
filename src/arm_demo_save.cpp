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

    char* fname,* ftemp;
    if(argc>1)
    {fname = argv[1];}
    else
    {fname="demo.txt";ftemp="demo_temp.txt";}

    std::fstream fs_temp(ftemp,std::fstream::out | std::fstream::trunc);
    std::fstream fs;
    fs.close();

    int32_t pos[4];
    for(int id=1;id<5;id++)
    {
        Chain.monitorParam(id,"Present Position");
    }

    int nb_poses = 0;

    while(true)
    {
        std::cout << "Press r to record current positions, c to record positions where the gripper should close, o where it should open or q to quit\n";
        char c;
        std::cin >> c;
        if(c=='r')
        {
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            for(int i=1;i<5;i++)
            {
                // std::cout << (long)*(pos+(i-1)) << "\t";
                fs_temp << (long)*(pos+(i-1)) << "\t";
            }
            // std::cout << (long)*(pos+3) << "\n";
            fs_temp << (int)0 << "\n";
            std::cout << "Pose : " << ++nb_poses << std::endl;
        }
        else if(c=='c')
        {
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            for(int i=1;i<5;i++)
            {
                // std::cout << (long)*(pos+(i-1)) << "\t";
                fs_temp << (long)*(pos+(i-1)) << "\t";
            }
            // std::cout << (long)*(pos+3) << "\n";
            fs_temp << (int)200 << "\n";
            std::cout << "Pose : " << ++nb_poses << std::endl;
        }
        else if(c=='o')
        {
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            for(int i=1;i<5;i++)
            {
                // std::cout << (long)*(pos+(i-1)) << "\t";
                fs_temp << (long)*(pos+(i-1)) << "\t";
            }
            // std::cout << (long)*(pos+3) << "\n";
            fs_temp << (int)-200 << "\n";
            std::cout << "Pose : " << ++nb_poses << std::endl;
        }
        else if(c=='q')
        {
            fs_temp.close();
            fs_temp.open(ftemp,std::fstream::in);
            fs.open(fname,std::fstream::out);
            fs << nb_poses << std::endl;
            char temp[100];
            do {
                fs_temp.getline(temp,100);
                fs << temp << std::endl;
            } while(!fs_temp.eof());
            fs.close();
            break;
        }
    }
    return 0;
}
