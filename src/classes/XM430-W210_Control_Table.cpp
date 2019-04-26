#include "XM430-W210_Control_Table.h"
#include <iostream>

// XM430-W210 actuator registers
dxl_registers_struct_type dxl_reg_XM430_W210[] =	{
    {	DXL_REG_MEM_EEPROM, 0,		2,	"XM430-W210", "Model number",
        DXL_REG_ACCESS_R, 1030,
        DXL_REG_TYPE_UINT16, 0, 65535, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 2,		4,	"Model Information", "Model Information",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT32, 0, 0, 0.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 6,		1,	"Firmware Version", "Version of Firmware",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT8, 0, 255, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 7,		1,	"ID", "ID,Dynamixel",
        DXL_REG_ACCESS_RW, 1,
        DXL_REG_TYPE_UINT8, 0, 255, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 8,		1,	"Baud Rate", "Communication Baud Rate",
        DXL_REG_ACCESS_RW, 1,
        DXL_REG_TYPE_UINT8, 0, 7, 1.0, DXL_REG_NO_UNIT },
        /* Defines serial communication speed :
        0 : 9,600
        1 : 57,600
        2 : 115,200
        3 : 1M
        4 : 2M
        5 : 3M
        6 : 4M
        7 : 4.5M
        */

    {	DXL_REG_MEM_EEPROM, 9,		1,	"Return Delay Time", "Response Delay Time",
        DXL_REG_ACCESS_RW, 250,
        DXL_REG_TYPE_UINT8, 0, 254, 2.0, "us" },

    {	DXL_REG_MEM_EEPROM, 10,		1,	"Drive Mode", "Drive Mode",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT8, 0, 5, 1.0, DXL_REG_NO_UNIT },
        /* Defines direction of rotation and profile :
        0 : Normal Mode (CCW=positive) & Velocity-based profile
        1 : Reverse Mode (CCW=negative) & Velocity-based profile
        4 : Normal Mode (CCW=positive) & Time-based profile
        5 : Reverse Mode (CCW=negative) & Time-based profile
        */

    {	DXL_REG_MEM_EEPROM, 11,		1,	"Operating Mode", "Operating Mode",
        DXL_REG_ACCESS_RW, 3,
        DXL_REG_TYPE_UINT8, 0, 16, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 13,		1,	"Protocol Version", "Protocol Version",
        DXL_REG_ACCESS_RW, 2,
        DXL_REG_TYPE_UINT8, 1, 2, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_EEPROM, 20,		4,	"Homing Offset", "Home Position Offset",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_SINT32, -1044479, 1044479, 0.087890625, "deg" },

    {	DXL_REG_MEM_EEPROM, 24,		4,	"Moving Threshold", "Velocity Threshold for Movement Detection",
        DXL_REG_ACCESS_RW, 10,
        DXL_REG_TYPE_SINT32, -1044479, 1044479, 0.087890625, "deg" },

    {	DXL_REG_MEM_EEPROM, 31,		1,	"Temperature Limit", "Maximum Internal Temperature Limit",
        DXL_REG_ACCESS_RW, 80,
        DXL_REG_TYPE_UINT8, 0, 100, 1.0, "°C" },

    {	DXL_REG_MEM_EEPROM, 32,		2,	"Max Voltage Limit", "Maximum Voltage Limit",
        DXL_REG_ACCESS_RW, 160,
        DXL_REG_TYPE_UINT16, 95, 160, 0.1, "V" },

    {	DXL_REG_MEM_EEPROM, 34,		2,	"Min Voltage Limit", "Minimum Voltage Limit",
        DXL_REG_ACCESS_RW, 95,
        DXL_REG_TYPE_UINT16, 95, 160, 0.1, "V" },

    {	DXL_REG_MEM_EEPROM, 36,		2,	"PWM Limit", "Maximum PWM Limit",
        DXL_REG_ACCESS_RW, 885,
        DXL_REG_TYPE_UINT16, 0, 885, 0.11299435028249, "%" },

    {	DXL_REG_MEM_EEPROM, 38,		2,	"Current Limit", "Maximum Current Limit",
        DXL_REG_ACCESS_RW, 1193,
        DXL_REG_TYPE_UINT16, 0, 1193, 2.69, "mA" },

    {	DXL_REG_MEM_EEPROM, 40,		4,	"Acceleration Limit", "Maximum Acceleration Limit",
        DXL_REG_ACCESS_RW, 32767,
        DXL_REG_TYPE_UINT32, 0, 32767, 0.0036, "RPM/min" },

    {	DXL_REG_MEM_EEPROM, 44,		4,	"Velocity Limit", "Maximum Velocity Limit",
        DXL_REG_ACCESS_RW, 480,
        DXL_REG_TYPE_UINT32, 0, 1023, 0.229, "RPM" },

    {	DXL_REG_MEM_EEPROM, 48,		4,	"Max Position Limit", "Maximum Position Limit",
        DXL_REG_ACCESS_RW, 4095,
        DXL_REG_TYPE_UINT32, 0, 4095, 0.087890625, "deg" },

    {	DXL_REG_MEM_EEPROM, 52,		4,	"Min Position Limit", "Minimum Position Limit",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT32, 0, 4095, 0.087890625, "deg" },

    {	DXL_REG_MEM_EEPROM, 63,		1,	"Shutdown", "Shutdown Dynamixel",
        DXL_REG_ACCESS_RW, 52,
        DXL_REG_TYPE_UINT8, 0, 255, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		64,		1,	"Torque Enable", "Motor Torque On/Off",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT8, 0, 1, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		65,		1,	"LED", "Status LED On/Off",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT8, 0, 1, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		68,		1,	"Status Return Level", "Select Types of Status Return",
        DXL_REG_ACCESS_RW, 2,
        DXL_REG_TYPE_UINT8, 0, 2, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		69,		1,	"Registered Instruction", "Check Reception of Instruction",
        DXL_REG_ACCESS_R, 0,
        DXL_REG_TYPE_UINT8, 0, 1, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		70,		1,	"Hardware Error Status", "Hardware Error Status",
        DXL_REG_ACCESS_R, 0,
        DXL_REG_TYPE_UINT8, 0, 255, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		76,		2,	"Velocity I Gain", "I Gain of Velocity",
        DXL_REG_ACCESS_RW, 1920,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		78,		2,	"Velocity P Gain", "P Gain of Velocity",
        DXL_REG_ACCESS_RW, 50,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		80,		2,	"Position D Gain", "D Gain of Position",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		82,		2,	"Position I Gain", "I Gain of Position",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		84,		2,	"Position P Gain", "P Gain of Position",
        DXL_REG_ACCESS_RW, 800,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		88,		2,	"Feedforward 2nd Gain", "2nd Gain of Feed-Forward",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		90,		2,	"Feedforward 1st Gain", "1st Gain of Feed-Forward",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		100,	2,	"Goal PWM", "Target PWM Value",
        DXL_REG_ACCESS_RW, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT16, -885, 885, 0.11299435028249, "%" },

    {	DXL_REG_MEM_RAM, 		102,	2,	"Goal Current", "Target Current Value",
        DXL_REG_ACCESS_RW, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT16, -1193, 1193, 2.69, "mA" },

    {	DXL_REG_MEM_RAM, 		104,	4,	"Goal Velocity", "Target Velocity Value",
        DXL_REG_ACCESS_RW, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT32, -1023, 1023, 0.229, "RPM" },

    {	DXL_REG_MEM_RAM, 		108,	4,	"Profile Acceleration", "Acceleration Value of Profile",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT32, 0, 32767, 0.0036, "RPM/min" },

    {	DXL_REG_MEM_RAM, 		112,	4,	"Profile Velocity", "Velocity Value of Profile",
        DXL_REG_ACCESS_RW, 0,
        DXL_REG_TYPE_UINT32, 0, 1023, 0.229, "RPM" },

    {	DXL_REG_MEM_RAM, 		116,	4,	"Goal Position", "Target Position Value",
        DXL_REG_ACCESS_RW, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT32, -1048575, 1048575, 0.087890625, "deg" },

    {	DXL_REG_MEM_RAM, 		120,	2,	"Realtime Tick", "Count Time in millisecond",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT16, 0, 32767, 1.0, "ms" },

    {	DXL_REG_MEM_RAM, 		122,	1,	"Moving", "Movement Status",
        DXL_REG_ACCESS_R, 0,
        DXL_REG_TYPE_UINT8, 0, 1, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		123,	1,	"Moving Status", "Detailed Information of Movement Status",
        DXL_REG_ACCESS_R, 0,
        DXL_REG_TYPE_UINT8, 0, 255, 1.0, DXL_REG_NO_UNIT },

    {	DXL_REG_MEM_RAM, 		124,	2,	"Present PWM", "Current PWM Value",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT16, -885, 885, 0.11299435028249, "%" },

    {	DXL_REG_MEM_RAM, 		126,	2,	"Present Current", "Current Current Value",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT16, -1193, 1193, 2.69, "mA" },

    {	DXL_REG_MEM_RAM, 		128,	4,	"Present Velocity", "Current Velocity Value",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT32, -1023, 1023, 0.229, "RPM" },

    {	DXL_REG_MEM_RAM, 		132,	4,	"Present Position", "Current Position Value",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT32, -1048575, 1048575, 0.087890625, "deg" },

    {	DXL_REG_MEM_RAM, 		136,	4,	"Velocity Trajectory", "Target Velocity Trajectory Generated by Profile",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT32, 0, 1023, 0.229, "RPM" },

    {	DXL_REG_MEM_RAM, 		140,	4,	"Position Trajectory", "Target Position Trajectory Generated by Profile",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_SINT32, -1048575, 1048575, 0.087890625, "deg" },

    {	DXL_REG_MEM_RAM, 		144,	2,	"Present Input Voltage", "Current Input Voltage",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT16, 0, 255, 0.1, "V" },

    {	DXL_REG_MEM_RAM, 		146,	1,	"Present Temperature", "Current Internal Temperature",
        DXL_REG_ACCESS_R, DXL_REG_UNDEFINED_INITIAL_VALUE,
        DXL_REG_TYPE_UINT8, 0, 100, 1.0, "°C" },

    {	DXL_REG_MEM_END, 		147, 0, "", "", 0, 0, 0, 0, 0, 0.0, "" }
};

dxl_control_table XM430_W210_control_table;

void createControlTable()
{
    for (int i=0;i<50;i++)
    {
        XM430_W210_control_table[dxl_reg_XM430_W210[i].short_description] = dxl_reg_XM430_W210[i];
    }
}
