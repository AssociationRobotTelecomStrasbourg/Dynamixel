#ifndef XM_BULK_CHAIN
#define XM_BULK_CHAIN

#include <cstdint>

#include <set>
#include <unordered_map>

class XM_bulk_chain
{
    private :
        int port_num_;
        int groupread_num_;
        int groupwrite_num_;
        std::set<uint8_t> id_list_;
        std::unordered_map<uint8_t,char*> param_monitor_list_;
    public :
        XM_bulk_chain(const uint8_t max_id=8, const int baudrate=57600, const char* port_name="/dev/ttyUSB0"); //construct id list for ids up to max_id
        ~XM_bulk_chain();

        std::set<uint8_t> getIDlist();

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

        bool setParam(uint8_t id, const char* paramName, const uint8_t paramValue);
        bool setParam(uint8_t id, const char* paramName, const int16_t paramValue);
        bool setParam(uint8_t id, const char* paramName, const uint16_t paramValue);
        bool setParam(uint8_t id, const char* paramName, const int32_t paramValue);
        bool setParam(uint8_t id, const char* paramName, const uint32_t paramValue);
        bool write(); //send packet with the parameters set with setParam

        bool monitorParam(uint8_t id, char* paramName);
        bool poll(); //poll dynamixel to get a packet containing the data set with monitorParam
        void getData(uint8_t id, uint8_t& d); //get monitored parameter set with monitorParam from packet received after the call of poll
        void getData(uint8_t id, int16_t& d);
        void getData(uint8_t id, uint16_t& d);
        void getData(uint8_t id, int32_t& d);
        void getData(uint8_t id, uint32_t& d);
};

#endif
