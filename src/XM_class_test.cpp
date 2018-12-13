#include "XM_class.h"
#include "XM430-W210_Control_Table.h"
#include <iostream>

extern "C"
{
    #include <ncurses.h>
    #include <stdlib.h>
}

#define DX_ID 1

WINDOW *scrn;

int main(int argc, char** argv)
{
    uint32_t goal_vel = 20; // default velocity
    if (argc > 1)
    {goal_vel = atoi(argv[1]);}
    createControlTable();
    XM M1(DX_ID);
    M1.ledOn();
    M1.setOperatingMode(1);
    M1.torqueOn();
    bool success = M1.setGoalVelocity(goal_vel);
    if(!success)
    {
        std::cout << "Could not set goal velocity...Exiting" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Succeeded in writing goal velocity to " << goal_vel <<"...Press any key to exit" << std::endl;
        scrn = initscr();
        noecho();
        cbreak();
        nodelay(scrn,TRUE);
        uint32_t vel;
        while(true)
        {
            vel = M1.getPresentVelocity();
            clear();
            printw("Current velocity : %i", vel);
            refresh();
            if(getch()!=ERR)
            {
                endwin();
                std::cout << "Exiting...";
                break;
            }
        }
        M1.setGoalVelocity(0);
        M1.torqueOff();
        std::cout << "Done" << std::endl;
        return 0;
    }
}
