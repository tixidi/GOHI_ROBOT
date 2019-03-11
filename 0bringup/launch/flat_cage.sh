
#!/bin/bash

roslaunch gohi_hw_flat_car gohi_hw_flat_car.launch  &
echo "gohi_hw_flat_car starting success!"
sleep 1


roslaunch gohi_hw_power_car gohi_hw_power_car.launch  &
echo "gohi_hw_power_car starting success!"
sleep 1

roslaunch gohi_hw_stair_car gohi_hw_stair_car.launch  &
echo "gohi_hw_stair_car starting success!"
sleep 1

roslaunch gohi_hw_rev gohi_hw.launch   &
echo "gohi_hw_rev starting success!"
sleep 1

roslaunch gohi_hw_sensor gohi_hw.launch 
echo "gohi_hw_sensor starting success!"
sleep 1


#roslaunch gohi_hw_idnev gohi_hw.launch 
#echo "gohi_hw_idnev starting success!"
#sleep 1

wait
exit 0
