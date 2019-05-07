#!/bin/bash

z=$(($1*3))

sudo python 3_Test_reel_v2_avecCamera.py | xargs python coord2angle.py | xargs ./arm_pump_control.exe
sleep 1
python coord2angle.py 21.5 0 $((z+2)) 90 1| xargs ./arm_pump_control.exe
sleep 1
python coord2angle.py 0 20 z 90 0| xargs ./arm_pump_control.exe
sleep 1
python coord2angle.py 0 20 $((z+2)) 90 0| xargs ./arm_pump_control.exe
sleep 1
python coord2angle.py 21.5 0 15 90 0| xargs ./arm_pump_control.exe