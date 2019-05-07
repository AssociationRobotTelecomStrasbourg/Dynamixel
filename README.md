# Dynamixel
C++ library for dynamixel motors (XM430-W210 at the moment).

## Content
### dynamixel_sdk_c
C source code used in the library.
Source : [Robotis](https://github.com/ROBOTIS-GIT/DynamixelSDK)
### src and include
C++ code aiming to facilitate the use of the dynamixel motors :
* classes
  * Control_Table contains structures storing info on control items (name, data type, length, ...)
  * XM_class : initialization and control of a unique motor
  * XM_bulk_chain : initialization and control of several motors with different control items simultaneously
  * XM_sync_chain : initialization and control of several motors with a unique control item at a given time (TODO)
* PID_tuning : used to test PID settings
* utilities : various programmes intended for debugging or as examples
* demo : demonstrations for the arm using the dynamixels (Engineering Project)
### python
python programme to convert 3D coordinates in angular positions for each motor in the arm
### doc
pdf file to explain how to use the motors
### BerryArm
implementation on RaspberryPi platform (not functional as PixyCam modules are missing)

## How to use
To compile this library :
- git clone https://github.com/AssociationRobotTelecomStrasbourg/Dynamixel.git
- cd ARTS_Dynamixel
- mkdir bin build lib && cd build
- cmake ..
- make

## To do
- Complete documentation
- Create sync functions class & methods
- Revise control table to make its use generic
