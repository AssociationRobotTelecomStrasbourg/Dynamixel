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
    if(argc==7)
    {
        int setpriosuccess;
        setpriosuccess = setpriority(PRIO_PROCESS,0,-20);

        if(!setpriosuccess)
        {
            createControlTable();
            XM_bulk_chain Chain(4,1000000);

            uint8_t id2test = atoi(argv[1]);

            int32_t pos_init[4]={atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5])};
            for(int id=1;id<5;id++)
            {
                Chain.setParam(id,"Goal Position",*(pos_init+id-1));
            }
            Chain.write();

            int32_t init_pos, goal_pos;
            int32_t pos;
            std::fstream fs;
            char filename[60];
            char output[30];

            std::chrono::steady_clock::time_point t,t_sampling;
            std::chrono::steady_clock::duration time_diff,time_diff_sampling;
            double sample_time;
            double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

            uint16_t P_gain=atoi(argv[2]);
            uint16_t I_gain=atoi(argv[3]);
            uint16_t D_gain=atoi(argv[4]);
            Chain.monitorParam(id2test,"Position P Gain");
            Chain.poll();
            Chain.getData(id2test,P_gain);
            Chain.monitorParam(id2test,"Position I Gain");
            Chain.poll();
            Chain.getData(id2test,I_gain);
            Chain.monitorParam(id2test,"Position D Gain");
            Chain.poll();
            Chain.getData(id2test,D_gain);

            sprintf(filename,"accuracy_results/accuracy%d_P%dI%dD%d.txt",id2test,P_gain,I_gain,D_gain);
            fs.open(filename,std::fstream::out | std::fstream::trunc);
            fs << "# Time   pos    goal_pos" << std::endl;

            std::this_thread::sleep_for (std::chrono::seconds(2));

            Chain.monitorParam(id2test,"Present Position");
            Chain.poll();
            Chain.getData(id2test,init_pos);

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
                    sprintf(output,"%.3f\t%d\t%d",sample_time,pos,goal_pos);
                    fs << output << std::endl;
                    // std::cerr << "Debug:" << sample_time << std::endl;
                    t_sampling=std::chrono::steady_clock::now();
                }
            } while((time_diff.count()*time_ratio)<=0.5);

            goal_pos = atoi(argv[6]);
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
                    sprintf(output,"%.3f\t%d\t%d",sample_time,pos,goal_pos);
                    fs << output << std::endl;
                    // std::cerr << "Debug:" << sample_time << std::endl;
                    t_sampling=std::chrono::steady_clock::now();
                }
            } while((time_diff.count()*time_ratio)<=5.0);
            fs.close();
        }
        else
        {
            std::cerr << "Error: Could not set priority" << std::endl;
        }
    }
    else
    {
        std::cerr << "usage: arm_accuracy_test.exe id pos1 pos2 pos3 pos4 goal_pos4id" << std::endl;
    }
}
