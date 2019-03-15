#include "XM_bulk_chain.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <thread>
#include <ratio>
#include <chrono>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/resource.h>
}

int main(int argc, char** argv)
{
    createControlTable();
    XM_bulk_chain Chain(4,1000000);

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

    if(argc>5)
    {
        uint8_t id2test = atoi(argv[1]);
        int32_t goal_pos;
        int32_t pos,init_pos;

        std::cout << "Initializing PID..." << std::endl;
        uint16_t P_gain=atoi(argv[3]);
        uint16_t I_gain=atoi(argv[4]);
        uint16_t D_gain=atoi(argv[5]);
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

        std::fstream fs;
        char filename[60];
        char output[30];

        std::chrono::steady_clock::time_point t,t_sampling;
        std::chrono::steady_clock::duration time_diff,time_diff_sampling;
        double sample_time;
        double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

        Chain.monitorParam(id2test,"Present Position");
        Chain.poll();
        Chain.getData(id2test,init_pos);
        sprintf(filename,"accuracy_results/accuracy%d_%04d_%04d_P%dI%dD%d.txt",id2test,init_pos,atoi(argv[2]),P_gain,I_gain,D_gain);
        fs.open(filename,std::fstream::out | std::fstream::trunc);

        goal_pos=init_pos;
        t = std::chrono::steady_clock::now();
        t_sampling = std::chrono::steady_clock::now();
        do {
            time_diff_sampling = std::chrono::steady_clock::now()-t_sampling;
            time_diff = std::chrono::steady_clock::now()-t;
            if(time_diff_sampling.count()*time_ratio>=0.00400)
            {
                sample_time = time_diff.count()*time_ratio;
                Chain.poll();
                Chain.getData(id2test,pos);
                sprintf(output,"%d\t%d\t%.3f",goal_pos,pos,sample_time);
                fs << output << std::endl;
                // std::cerr << "Debug:" << sample_time << std::endl;
                t_sampling=std::chrono::steady_clock::now();
            }
        } while((time_diff.count()*time_ratio)<=0.5);

        goal_pos = atoi(argv[2]);
        Chain.setParam(id2test,"Goal Position",goal_pos);
        Chain.write();

        do {
            time_diff_sampling = std::chrono::steady_clock::now()-t_sampling;
            time_diff = std::chrono::steady_clock::now()-t;
            if(time_diff_sampling.count()*time_ratio>=0.00400)
            {
                sample_time = time_diff.count()*time_ratio;
                Chain.poll();
                Chain.getData(id2test,pos);
                sprintf(output,"%d\t%d\t%.3f",goal_pos,pos,sample_time);
                fs << output << std::endl;
                // std::cerr << "Debug:" << sample_time << std::endl;
                t_sampling=std::chrono::steady_clock::now();
            }
        } while((time_diff.count()*time_ratio)<=10.0);
        fs.close();
    }
    else
    {
        std::cerr << "Error: Not enough arguments (id and goal position)" << std::endl;
    }
}
