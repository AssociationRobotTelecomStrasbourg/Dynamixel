#include "XM_class.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <thread>
#include <chrono>

extern "C"
{
    #include <stdlib.h>
    #include <stdio.h>
}

int main(int argc,char** argv)
{
    createControlTable();
    XM* Motor;
    std::fstream fs;

    if(argc>1)
    {
        if(!strcmp(argv[1],"--change-baudrate"))
        {
            int baudrate_old = atoi(argv[2]);
            int baudrate_new = atoi(argv[3]);
            std::cerr << "Debug : " << baudrate_old << "\t" << baudrate_new << std::endl;
            Motor = new XM(1,baudrate_old);
            std::cerr << "Debug : Motor detected\n";
            uint8_t baudrate_new_code;
            switch (baudrate_new)
            {
                case 9600:
                    baudrate_new_code = 0;
                    break;
                case 57600:
                    baudrate_new_code = 1;
                    break;
                case 115200:
                    baudrate_new_code = 2;
                    break;
                case 1000000:
                    baudrate_new_code = 3;
                    break;
                case 2000000:
                    baudrate_new_code = 4;
                    break;
                case 3000000:
                    baudrate_new_code = 5;
                    break;
                case 4000000:
                    baudrate_new_code = 6;
                    break;
                case 4500000:
                    baudrate_new_code = 7;
                    break;
                default:
                    std::cerr << "Invalid new baudrate" << '\n';
                    break;
            }
            std::cerr << "Debug : " << (int)baudrate_new_code << std::endl;
            bool success = Motor->generic_write("Baud Rate",baudrate_new_code);
            delete Motor;
            if(success)
            {
                std::cerr << "Succeeded in changing baudrate" << std::endl;
                Motor = new XM(1,baudrate_new);
            }
            else
            {
                std::cerr << "Failed in changing baudrate" << std::endl;
                return -1;
            }
        }
        else if(!strcmp(argv[1],"--help"))
        {
            std::cout << "usage : identification --change-baudrate old_baudrate new_baudrate\nor \nidentification --no-change baudrate" << std::endl;
            return 0;
        }
        else if(!strcmp(argv[1],"--no-change"))
        {
            int baudrate = atoi(argv[2]);
            Motor = new XM(1,baudrate);
        }
        else
        {
            std::cout << "usage : identification --change-baudrate old_baudrate new_baudrate\nor \nidentification --no-change baudrate" << std::endl;
            return 0;
        }
        std::cerr << "Debug : Setting P gain to 1" << std::endl;
        Motor->generic_write("Position P Gain",(uint16_t) 128);
        Motor->torqueOn();
        std::cerr << "Debug : Torque enabled" << std::endl;
        //std::cerr << "Debug : " << Motor->setGoalPosition(0);
        std::cerr << std::endl;
        int32_t goal_pos[3]={1024,2048,3072};
        int32_t pos;
        char filename[20];
        clock_t t,t_tempo,t_sampling;
        //std::cerr << "Debug : Clock object created" << std::endl;
        uint8_t mov_stat;
        for(int i=0;i<3;i++)
        {
            sprintf(filename,"dataset%d.txt",i);
            std::cerr << "Debug : " << filename << std::endl;
            Motor->setGoalPosition(0);
            fs.open(filename,std::fstream::out | std::fstream::trunc);
            fs << goal_pos[i] << "\t" << 0.0 << std::endl;
            do {
                Motor->generic_read("Moving Status",mov_stat);
            } while((!(mov_stat & 00000001)) && (!(mov_stat & 0001000)));
            pos = Motor->getPresentPosition();
            fs << pos << "\t" << 0.0 << std::endl;
            std::cout << "Waiting for start...";
            std::cin.get();
            Motor->setGoalPosition(goal_pos[i]);
            //std::cerr << "Debug : Goal " << (long)goal_pos[i] << std::endl;
            t = clock();
            do {
                if((double)(clock()-t_sampling)/CLOCKS_PER_SEC>0.05)
                {
                    pos = Motor->getPresentPosition();
                    fs << pos << "\t" << (double)(clock()-t)/CLOCKS_PER_SEC << std::endl;
                    //std::cerr << "Debug:" << pos << "\t" << goal_pos[i] << "\t" << abs(pos-goal_pos[i]) << std::endl;
                    t_sampling=clock();
                }
                Motor->generic_read("Moving Status",mov_stat);
            } while((!(mov_stat & 00000001)) && (!(mov_stat & 0001000)));
            t_tempo = clock();
            do {
                if((double)(clock()-t_sampling)/CLOCKS_PER_SEC>0.05)
                {
                    pos = Motor->getPresentPosition();
                    fs << pos << "\t" << (double)(clock()-t)/CLOCKS_PER_SEC << std::endl;
                    //std::cerr << "Debug:" << pos << "\t" << goal_pos[i] << "\t" << abs(pos-goal_pos[i]) << std::endl;
                    t_sampling=clock();
                }
            } while((double)(clock()-t_tempo)/CLOCKS_PER_SEC<0.5);
            fs.close();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        Motor->torqueOff();
    }
    else
    {
        std::cout << "usage : identification --change-baudrate old_baudrate new_baudrate\nor \nidentification --no-change baudrate" << std::endl;
        return 0;
    }
}
