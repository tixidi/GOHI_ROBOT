#!/bin/bash

echo 'KERENL=="usb 1-3",ATTRS{idVendor}=="10c4",ATTRS{idProduct}=="ea60",MODE:="0666",GROUP:="dialout",SYMLINK+="ttyUSB00001"' > /etc/udev/rules.d/ttyUSB00001.rules

service udev reload
sleep 2
service udev restart
