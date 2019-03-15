#ifndef XM_CLASS_H
#define XM_CLASS_H

#include <cstdint>

class XM
{
    private :
        int port_num_;
        uint8_t id_;
    public :
        XM(const uint8_t id=1, const int baudrate=57600, const char* port_name="/dev/ttyUSB0");
        ~XM();

        bool changeID(uint8_t id);
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

        bool setGoalPosition(int32_t goal_pos); //NB:true means operation succeeded
        bool setGoalVelocity(int32_t goal_vel);
        bool setGoalCurrent(int16_t goal_cur);

        int32_t getPresentPosition();
        int32_t getPresentVelocity();
        int16_t getPresentCurrent();

        bool generic_write(const char* paramName, uint8_t paramValue); //access any control table item using name defined in "XM430_W210_Control_Table.h"
        bool generic_write(const char* paramName, int8_t paramValue);
        bool generic_write(const char* paramName, uint16_t paramValue);
        bool generic_write(const char* paramName, int16_t paramValue);
        bool generic_write(const char* paramName, uint32_t paramValue);
        bool generic_write(const char* paramName, int32_t paramValue);

        bool generic_read(const char* paramName, uint8_t& paramValue);
        bool generic_read(const char* paramName, int8_t& paramValue);
        bool generic_read(const char* paramName, uint16_t& paramValue);
        bool generic_read(const char* paramName, int16_t& paramValue);
        bool generic_read(const char* paramName, uint32_t& paramValue);
        bool generic_read(const char* paramName, int32_t& paramValue);
};

#endif // XM_CLASS_H
