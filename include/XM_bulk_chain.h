#ifndef XM_BULK_CHAIN
#define XM_BULK_CHAIN

extern "C"
{
    #include "robotis_def.h"
}

#include <vector>

class XM_bulk_chain
{
    private :
        int port_num_;
        int groupread_num_;
        int groupwrite_num_;
        std::vector<uint8_t> id_list_;
    public :
        XM_bulk_chain(const char* port_name="/dev/ttyUSB0", const int baudrate=57600);
        ~XM_bulk_chain();

        void reset(uint8_t id); // 0xFF : all parameters; 0x01 : all but ID; 0x02 : all but ID and baudrate
        void reboot(uint8_t id);

        void ledOn(uint8_t id);
        void ledOff(uint8_t id);

        void torqueOn(uint8_t id);
        void torqueOff(uint8_t id);

        void setDriveMode(uint8_t id, const uint8_t drive_mode);
        /*0 : Normal Mode (CCW=positive) & Velocity-based profile
        1 : Reverse Mode (CCW=negative) & Velocity-based profile
        4 : Normal Mode (CCW=positive) & Time-based profile
        5 : Reverse Mode (CCW=negative) & Time-based profile*/
        void setOperatingMode(uint8_t id, const uint8_t operating_mode);
        /*0 : Current Control Mode
        1 : Velocity Control Mode
        3 : Position Control Mode
        4 : Extended Position Control Mode (multi-turn up to 512 turns)
        5 : Current-based Position Control Mode (controls both position and torque, up to 512 turns)
        16 : PWM Control Mode (not implemented here)*/

        bool setGoalPosition(uint8_t id, uint32_t goal_pos);
        bool setGoalVelocity(uint8_t id, uint32_t goal_vel);
        bool setGoalCurrent(uint8_t id, uint32_t goal_cur);

        bool monitorParam(uint8_t id, const char* paramName);

};

#endif
