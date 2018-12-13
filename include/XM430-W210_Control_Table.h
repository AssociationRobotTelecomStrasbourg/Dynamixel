#ifndef XM430_W210_CONTROL_TABLE_H
#define XM430_W210_CONTROL_TABLE_H

// Control table items for XM430-W210
// ITEM_ADDR is the address of the item
// ITEM_SIZE is the size in bytes of the item
// See http://emanual.robotis.com/docs/en/dxl/x/xm430-w210/ for more info

// EEPROM Area

#define XM_ID_NAME "ID"
#define XM_ID_ADDR 7
#define XM_ID_SIZE 1
#define XM_ID_RANGE [0,253] // default : 1

#define XM_BAUDRATE_NAME "Baudrate"
#define XM_BAUDRATE_ADDR 8
#define XM_BAUDRATE_SIZE 1
#define XM_BAUDRATE_RANGE [0,7] // default : 1
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

#define XM_DRIVE_MODE_NAME "Drive_Mode"
#define XM_DRIVE_MODE_ADDR 10
#define XM_DRIVE_MODE_SIZE 1
#define XM_DRIVE_MODE_RANGE [0,5] // default : 0
/* Defines direction of rotation and profile :
0 : Normal Mode (CCW=positive) & Velocity-based profile
1 : Reverse Mode (CCW=negative) & Velocity-based profile
4 : Normal Mode (CCW=positive) & Time-based profile
5 : Reverse Mode (CCW=negative) & Time-based profile
*/

#define XM_OPERATING_MODE_NAME "Operating_Mode"
#define XM_OPERATING_MODE_ADDR 11
#define XM_OPERATING_MODE_SIZE 1
#define XM_OPERATING_MODE_RANGE [0,16] // default : 3
/* Defines control mode :
0 : Current Control Mode
1 : Velocity Control Mode
3 : Position Control Mode
4 : Extended Position Control Mode (multi-turn up to 512 turns)
5 : Current-based Position Control Mode (controls both position and torque, up to 512 turns)
16 : PWM Control Mode (not implemented here)
*/

#define XM_HOMING_OFFSET_NAME "Homing_Offset"
#define XM_HOMING_OFFSET_ADDR 20
#define XM_HOMING_OFFSET_SIZE 4
#define XM_HOMING_OFFSET_RANGE [-1044479,1044479] // default : 0 ; unit : 1 pulse

#define XM_CURRENT_LIMIT_NAME "Current_Limit"
#define XM_CURRENT_LIMIT_ADRR 38
#define XM_CURRENT_LIMIT_SIZE 2
#define XM_CURRENT_LIMIT_RANGE [0,1193] // default : 1193 ; unit : 2.69 mA

#define XM_VELOCITY_LIMIT_NAME "Velocity_Limit"
#define XM_VELOCITY_LIMIT_ADDR 44
#define XM_VELOCITY_LIMIT_SIZE 4
#define XM_VELOCITY_LIMIT_RANGE [0,1023] // default : 330 ; unit : 0.229 rev/min

#define XM_MAX_POSITION_LIMIT_NAME "Max_Position_Limit"
#define XM_MAX_POSITION_LIMIT_ADRR 48
#define XM_MAX_POSITION_LIMIT_SIZE 4
#define XM_MAX_POSITION_LIMIT_RANGE [0,4095] // default : 4095 ; unit : 1 pulse

#define XM_MIN_POSITION_LIMIT_NAME "Min_Position_Limit"
#define XM_MIN_POSITION_LIMIT_ADRR 52
#define XM_MIN_POSITION_LIMIT_SIZE 4
#define XM_MIN_POSITION_LIMIT_RANGE [0,4095] // default : 0 ; unit : 1 pulse

// RAM Area

#define XM_TORQUE_ENABLE_NAME "Torque_Enable"
#define XM_TORQUE_ENABLE_ADDR 64
#define XM_TORQUE_ENABLE_SIZE 1
#define XM_TORQUE_ENABLE_RANGE [0,1] // default : 0

#define XM_LED_NAME "LED"
#define XM_LED_ADDR 65
#define XM_LED_SIZE 1
#define XM_LED_RANGE [0,1] // default : 0

#define XM_GOAL_CURRENT_NAME "Goal_Current"
#define XM_GOAL_CURRENT_ADDR 102
#define XM_GOAL_CURRENT_SIZE 2
#define XM_GOAL_CURRENT_RANGE [-Current_Limit,Current_Limit] // unit : 2.69 mA

#define XM_GOAL_VELOCITY_NAME "Goal_Velocity"
#define XM_GOAL_VELOCITY_ADDR 104
#define XM_GOAL_VELOCITY_SIZE 4
#define XM_GOAL_VELOCITY_RANGE [-Velocity_Limit,Velocity_Limit] // unit : 0.229 rev/min

#define XM_PROFILE_ACCELERATION_NAME "Profile_Acceleration"
#define XM_PROFILE_ACCELERATION_ADDR 108
#define XM_PROFILE_ACCELERATION_SIZE 4
#define XM_PROFILE_ACCELERATION_RANGE_VELOCITY_BASED [0,32767] // default : 0 ; unit : 214.577 rev/min²
#define XM_PROFILE_ACCELERATION_RANGE_TIME_BASED [0,32737] // default : 0 ; unit : 1 ms

#define XM_PROFILE_VELOCITY_NAME "Profile_Velocity"
#define XM_PROFILE_VELOCITY_ADDR 112
#define XM_PROFILE_VELOCITY_SIZE 4
#define XM_PROFILE_VELOCITY_RANGE [0,32767] // default : 0 ; unit : 0.229 rev/min

#define XM_GOAL_POSITION_NAME "Goal_Position"
#define XM_GOAL_POSITION_ADDR 116
#define XM_GOAL_POSITION_SIZE 4
#define XM_GOAL_POSITION_RANGE [Min_Position_Limit,Max_Position_Limit] // unit : 1 pulse

#define XM_PRESENT_CURRENT_NAME "Present_Current"
#define XM_PRESENT_CURRENT_ADDR 126
#define XM_PRESENT_CURRENT_SIZE 2
// unit : 2.69 mA

#define XM_PRESENT_VELOCITY_NAME "Present_Velocity"
#define XM_PRESENT_VELOCITY_ADDR 128
#define XM_PRESENT_VELOCITY_SIZE 4
// unit : 0.229 rev/min

#define XM_PRESENT_POSITION_NAME "Present_Position"
#define XM_PRESENT_POSITION_ADDR 132
#define XM_PRESENT_POSITION_SIZE 4
// unit : 1 pulse

#define XM_VELOCITY_TRAJECTORY_NAME "Velocity_Trajectory"
#define XM_VELOCITY_TRAJECTORY_ADDR 136
#define XM_VELOCITY_TRAJECTORY_SIZE 4
// unit : 0.229 rev/min

#define XM_POSITION_TRAJECTORY_NAME "Position_Trajectory"
#define XM_POSITION_TRAJECTORY_ADDR 140
#define XM_POSITION_TRAJECTORY_SIZE 4
// unit : 1 pulse

#endif // XM430_W210_CONTROL_TABLE_H
