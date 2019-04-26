#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <thread>
#include <ratio>
#include <chrono>
#include <future>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/resource.h>
}

int main(int argc, char** argv)
{
    if (argc>1)
    {
        int setpriosuccess;
        setpriosuccess = setpriority(PRIO_PROCESS,0,-20);

        if(!setpriosuccess)
        {
            createControlTable();
            XM_bulk_chain Chain(4,1000000);

            int32_t pos[4];

            std::fstream fs;
            char filename[60];

            std::chrono::steady_clock::time_point t, t_sampling;
            std::chrono::steady_clock::duration time_diff, time_diff_sampling;
            double sample_time;
            double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

            if(argc==2)
            {
                //Learning
                char output[30];

                char exit_sig_char = ' ';
                int exit_sig=0;

                for(int id=1;id<5;id++)
                {
                    Chain.monitorParam(id,"Present Position");
                }

                sprintf(filename,"learn2write_%s.txt",argv[1]);
                fs.open(filename,std::fstream::out | std::fstream::trunc);

                std::cerr << "Realize the pattern to learn manually. Press ENTER to begin saving and press ENTER again to exit." << std::endl;
                std::cin.get();

                auto exit_sig_fut = std::async(std::launch::async, static_cast<std::istream&(std::istream::*)(char&)>(&std::istream::get), &std::cin, std::ref(exit_sig_char));

                t = std::chrono::steady_clock::now();
                t_sampling = std::chrono::steady_clock::now();
                do {
                    time_diff_sampling = std::chrono::steady_clock::now()-t_sampling;
                    time_diff = std::chrono::steady_clock::now()-t;
                    if(time_diff_sampling.count()*time_ratio>=0.00400)
                    {
                        sample_time = time_diff.count()*time_ratio;
                        Chain.poll();
                        for(int id=1;id<5;id++)
                        {
                            Chain.getData(id,*(pos+id-1));
                        }
                        sprintf(output,"%d\t%d\t%d\t%d\t%.3f",*pos,*(pos+1),*(pos+2),*(pos+3),sample_time);
                        fs << output << std::endl;
                        // std::cerr << "Debug:" << sample_time << std::endl;
                        t_sampling=std::chrono::steady_clock::now();
                    }
                    exit_sig = (exit_sig_char!=' ');
                } while(!exit_sig);
                fs.close();
            }
            else
            {
                if(!strcmp("--load",argv[1]))
                {sprintf(filename,"learn2write_%s.txt",argv[2]);}
                else
                {std::cerr << "usage: learn2write.exe <word> or learn2write.exe <--load> <word>" << std::endl;}
            }

            //Writing
            std::cerr << "Press ENTER to go to the starting point." << std::endl;
            std::cin.get();

            // Go slowly to starting point
            std::cout << "Initializing velocity and acceleration profiles...";
            uint32_t pro_vel = 131;
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

            for (int id = 1; id < 5; id++)
            {
                Chain.torqueOn(id);
            }

            fs.open(filename,std::fstream::in);
            for(int id=1;id<5;id++)
            {
                fs >> *(pos+id-1);
                Chain.setParam(id,"Goal Position",*(pos+id-1));
            }
            fs.close();
            Chain.write();

            std::cerr << "Press ENTER to begin writing" << std::endl;
            std::cin.get();

            // Let the arm go fast enough to write correctly
            std::cout << "Initializing velocity and acceleration profiles...";
            pro_vel = 0;
            pro_acc = 0;
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

            double delay;
            int peek_value;
            fs.open(filename,std::fstream::in);
            t = std::chrono::steady_clock::now();
            do {
                for(int id=1;id<5;id++)
                {
                    fs >> *(pos+id-1);
                    Chain.setParam(id,"Goal Position",*(pos+id-1));
                }
                fs >> delay;
                // std::cerr << "Debug: delay " << delay << std::endl;
                peek_value = fs.peek();

                do {
                    time_diff = std::chrono::steady_clock::now()-t;
                    // std::cerr << "Debug:" << time_diff.count()*time_ratio << std::endl;
                } while((time_diff.count()*time_ratio)<delay);
                Chain.write();

            } while(peek_value!=EOF);
            fs.close();

            std::cerr << "Press ENTER to deactivate torque. Warning: doing so means the arm will fall if it's not secured" << std::endl;
            std::cin.get();

            for (int id = 1; id < 5; id++)
            {
                Chain.torqueOff(id);
            }
        }
        else
        {
            std::cerr << "Error: Could not set priority" << std::endl;
        }
    }
    else
    {
        std::cerr << "usage: learn2write.exe <word> or learn2write.exe <--load> <word>" << std::endl;
    }
}
