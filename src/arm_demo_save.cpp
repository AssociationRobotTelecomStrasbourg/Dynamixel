#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <list>
#include <string>

extern "C"
{
    #include <stdlib.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Chain(5,1000000);

    char cstr_save[60];
    std::list<std::string> save_str;
    char* fname;
    if(argc>1)
    {fname = argv[1];}
    else
    {fname="demo.txt";}

    std::fstream fs;

    int32_t pos[4];
    for(int id=1;id<5;id++)
    {
        Chain.monitorParam(id,"Present Position");
    }

    int nb_poses = 0;
    int goal_cur=0;

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
            // for(int i=1;i<4;i++)
            // {
            //     // std::cout << (long)*(pos+(i-1)) << "\t";
            //     fs_temp << (long)*(pos+(i-1)) << "\t";
            // }
            // fs_temp << goal_cur << "\n";
            sprintf(cstr_save,"%ld\t%ld\t%ld\t%ld\t%d\n",(long)*pos,(long)*(pos+1),(long)*(pos+2),(long)*(pos+3),goal_cur);
            save_str.push_back(cstr_save);
            std::cout << "Pose: " << ++nb_poses << std::endl;
            std::cout << "Saving: " << cstr_save;
        }
        else if(c=='c')
        {
            goal_cur = 200;
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            // for(int i=1;i<4;i++)
            // {
            //     // std::cout << (long)*(pos+(i-1)) << "\t";
            //     fs_temp << (long)*(pos+(i-1)) << "\t";
            // }
            // fs_temp << goal_cur << "\n";
            sprintf(cstr_save,"%ld\t%ld\t%ld\t%ld\t%d\n",(long)*pos,(long)*(pos+1),(long)*(pos+2),(long)*(pos+3),goal_cur);
            save_str.push_back(cstr_save);
            std::cout << "Pose: " << ++nb_poses << std::endl;
            std::cout << "Saving: " << cstr_save;
        }
        else if(c=='o')
        {
            goal_cur = -200;
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            // for(int i=1;i<4;i++)
            // {
            //     // std::cout << (long)*(pos+(i-1)) << "\t";
            //     fs_temp << (long)*(pos+(i-1)) << "\t";
            // }
            // fs_temp << goal_cur << "\n";
            sprintf(cstr_save,"%ld\t%ld\t%ld\t%ld\t%d\n",(long)*pos,(long)*(pos+1),(long)*(pos+2),(long)*(pos+3),goal_cur);
            save_str.push_back(cstr_save);
            std::cout << "Pose: " << ++nb_poses << std::endl;
            std::cout << "Saving: " << cstr_save;
            goal_cur = 0;
        }
        else if(c=='q')
        {
            fs.open(fname,std::fstream::out);
            fs << nb_poses << std::endl;
            std::cerr << "Debug: save_str contains " << save_str.size() << "strings" << std::endl;
            for(auto it = save_str.begin(); it != save_str.end(); it++)
            {
                std::cerr << "Debug: Writing " << *it;
                fs << *it;
            }
            fs.close();
            break;
        }
    }
    return 0;
}
