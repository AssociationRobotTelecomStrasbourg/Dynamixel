echo 1 | sudo tee /sys/bus/usb-serial/devices/ttyUSB0/latency_timer # sets USB latency to 1 ms
sudo chmod a+rw /dev/ttyUSB0 # allows programmes to read/write from/to port (ttyUSB0 is the default on Linux)
