# Dynamixel
C++ library for dynamixel motors (XM430-W210 at the moment).

## Content
### dynamixel_sdk_c
C source code used in the library.
Source : [Robotis](https://github.com/ROBOTIS-GIT/DynamixelSDK)
### XM_class and Control_Table
C++ code aiming to facilitate the use of the dynamixel motors :
- Control_Table contains structures storing info on control items (name, data type, length, ...)
- XM_class : initialization and control of a unique motor
- XM_bulk_chain : initialization and control of several motors with different control items simultaneously
- XM_sync_chain : initialization and control of several motors with a unique control item at a given time (TODO)

## How to use
To compile this library :
- git clone https://github.com/AssociationRobotTelecomStrasbourg/Dynamixel.git
- cd ARTS_Dynamixel
- mkdir bin build lib && cd build
- cmake ..
- make
