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
    XM_bulk_chain Chain(5);

    char* fname;
    if(argc>1)
    {fname = argv[1];}
    else
    {fname="demo.txt";}

    std::fstream fs(fname,std::fstream::out | std::fstream::trunc);
    fs.close();

    int32_t pos[4];
    for(int id=1;id<5;id++)
    {
        Chain.monitorParam(id,"Present Position");
    }

    int nb_poses = 0;

    while(true)
    {
        std::cout << "Press r to record current positions, s to start the demo (using the positions recorded) or q to quit\n";
        char c;
        std::cin >> c;
        if(c=='r')
        {
            fs.open(fname,std::fstream::out | std::fstream::app);
            Chain.poll();
            for(int id=1;id<5;id++)
            {
                Chain.getData(id,*(pos+(id-1)));
            }
            for(int i=1;i<4;i++)
            {
                // std::cout << (long)*(pos+(i-1)) << "\t";
                fs << (long)*(pos+(i-1)) << "\t";
            }
            // std::cout << (long)*(pos+3) << "\n";
            fs << (long)*(pos+3) << "\n";
            std::cout << "Pose : " << ++nb_poses << std::endl;
            std::cout << "Current positions saved to " << fname << std::endl;
            fs.close();
        }
        else if(c=='s')
        {
            std::cout << "Reading positions from " << fname << ". Please hit s to confirm\n";
            std::cin >> c;
            if(c=='s')
            {
                fs.open(fname, std::fstream::in);
                for(int id=1;id<5;id++)
                {
                    Chain.torqueOn(id);
                }
                for(int i=1;i<(nb_poses+1);i++)
                {
                    std::cout << "Pose : "<< i << "/" << nb_poses << std::endl;
                    for(int id=1;id<5;id++)
                    {
                        // std::cout << id << std::endl;
                        // std::cout << *(pos+(id-1)) << std::endl;
                        fs >> *(pos+(id-1));
                        std::cout << *(pos+(id-1)) << "\t";
                        Chain.setParam(id,"Goal Position",*(pos+(id-1)));
                    }
                    Chain.write();
                    std::cout << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                }
                fs.close();
            }
        }
        else if(c=='q')
        {
            std::cout << "Please secure the arm (stabilize it or prepare to catch it). Press q to confirm\n";
            std::cin >> c;
            if(c=='q')
            {
                for(int id=1;id<5;id++)
                {
                    Chain.torqueOff(id);
                }
                break;
            }
        }
    }
    return 0;
}
