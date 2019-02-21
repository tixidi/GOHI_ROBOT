#!/bin/bash

echo 'KERENL=="ttyUSB*",ATTRS{idVendor}=="046d",ATTRS{idProduct}=="c52f",MODE:="0666",GROUP:="dialout",SYMLINK+="ttyros1"' > /etc/udev/rules.d/ttyUSB00001.rules
echo 'KERENL=="ttyUSB*",ATTRS{idVendor}=="0bda",ATTRS{idProduct}=="5411",MODE:="0666",GROUP:="dialout",SYMLINK+="ttyros2"' > /etc/udev/rules.d/ttyUSB00001.rules
echo 'KERENL=="ttyUSB*",ATTRS{idVendor}=="1d6b",ATTRS{idProduct}=="0002",MODE:="0666",GROUP:="dialout",SYMLINK+="ttyros3"' > /etc/udev/rules.d/ttyUSB00001.rules


service udev reload
sleep 2
service udev restart
