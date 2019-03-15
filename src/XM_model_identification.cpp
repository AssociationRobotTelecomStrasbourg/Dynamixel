#include "XM_class.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <thread>
#include <ratio>
#include <chrono>
#include <iomanip>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/resource.h>
}

int main(int argc,char** argv)
{
    int setpriosuccess;
    setpriosuccess = setpriority(PRIO_PROCESS,0,-20);
    if(!setpriosuccess)
    {
        if(argc>2)
        {
            createControlTable();
            uint8_t id = atoi(argv[1]);
            XM Motor(id,1000000);

            std::fstream fs;

            std::cerr << "Debug : Setting operating mode to PWM" << std::endl;
            Motor.setOperatingMode((uint8_t) 16);
            uint8_t op_mode;
            Motor.generic_read("Operating Mode",op_mode);
            std::cerr << "Debug : Operating Mode Check " << (unsigned)op_mode << std::endl;

            Motor.torqueOn();
            std::cerr << "Debug : Torque enabled" << std::endl;

            int16_t goal_pwm = atoi(argv[2]);
            if(abs(goal_pwm)<=885)
            {
                int32_t pos;
                char filename[20];
                char output[20];

                // clock_t t,t_sampling;
                std::chrono::steady_clock::time_point t,t_sampling;
                std::chrono::steady_clock::duration time_diff,time_diff_sampling;
                double sample_time;
                double time_ratio = (double)std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

                sprintf(filename,"dataset%d_%03d.txt",id,goal_pwm);
                std::cerr << "Debug : " << filename << std::endl;

                Motor.generic_write("Goal PWM",(int16_t) 0);

                fs.open(filename,std::fstream::out | std::fstream::trunc);
                pos = Motor.getPresentVelocity();
                t = std::chrono::steady_clock::now();
                t_sampling = std::chrono::steady_clock::now();
                do {
                    time_diff_sampling = std::chrono::steady_clock::now()-t_sampling;
                    time_diff = std::chrono::steady_clock::now()-t;
                    if(time_diff_sampling.count()*time_ratio>=0.00400)
                    {
                        sample_time = time_diff.count()*time_ratio;
                        pos = Motor.getPresentVelocity();
                        sprintf(output,"%d\t%.3f",pos,sample_time);
                        fs << output << std::endl;
                        // std::cerr << "Debug:" << sample_time << std::endl;
                        t_sampling=std::chrono::steady_clock::now();
                    }
                } while((time_diff.count()*time_ratio)<=0.050);

                Motor.generic_write("Goal PWM",goal_pwm);

                do {
                    time_diff_sampling = std::chrono::steady_clock::now()-t_sampling;
                    time_diff = std::chrono::steady_clock::now()-t;
                    if(time_diff_sampling.count()*time_ratio>=0.00400)
                    {
                        sample_time = time_diff.count()*time_ratio;
                        pos = Motor.getPresentVelocity();
                        sprintf(output,"%d\t%.3f",pos,sample_time);
                        fs << output << std::endl;
                        // std::cerr << "Debug:" << sample_time << std::endl;
                        t_sampling=std::chrono::steady_clock::now();
                    }
                } while((time_diff.count()*time_ratio)<=0.500);

                fs.close();
                goal_pwm=0;
                Motor.generic_write("Goal PWM",goal_pwm);
                Motor.torqueOff();
            }
            else
            {
                std::cerr << "Wrong argument : Goal PWM exceeds 885 in absolute value" << std::endl;
            }
        }
        else
        {
            std::cerr << "usage : identification [id]" << std::endl;
        }
    }
    else
    {
        std::cerr << "Set priority failed. Exiting" << std::endl;
    }
    return 0;
}
