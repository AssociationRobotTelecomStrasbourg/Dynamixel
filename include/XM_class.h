#ifndef XM_CLASS_H
#define XM_CLASS_H

extern "C"
{
    #include "robotis_def.h"
}

class XM
{
    private :
        int port_num_;
        uint8_t id_;
    public :
        XM(const uint8_t id=1, const char* port_name="/dev/ttyUSB0", const int baudrate=57600);
        ~XM();

        void reset(uint8_t option=0x02); // 0xFF : all parameters; 0x01 : all but ID; 0x02 : all but ID and baudrate
        void reboot();

        void ledOn();
        void ledOff();

        void torqueOn();
        void torqueOff();

        void setDriveMode(const uint8_t drive_mode);
        /*0 : Normal Mode (CCW=positive) & Velocity-based profile
        1 : Reverse Mode (CCW=negative) & Velocity-based profile
        4 : Normal Mode (CCW=positive) & Time-based profile
        5 : Reverse Mode (CCW=negative) & Time-based profile*/
        void setOperatingMode(const uint8_t operating_mode);
        /*0 : Current Control Mode
        1 : Velocity Control Mode
        3 : Position Control Mode
        4 : Extended Position Control Mode (multi-turn up to 512 turns)
        5 : Current-based Position Control Mode (controls both position and torque, up to 512 turns)
        16 : PWM Control Mode (not implemented here)*/

        bool setGoalPosition(uint32_t goal_pos);
        bool setGoalVelocity(uint32_t goal_vel);
        bool setGoalCurrent(uint32_t goal_cur);

        uint32_t getPresentPosition();
        uint32_t getPresentVelocity();
        uint32_t getPresentCurrent();
};

#endif // XM_CLASS_H
