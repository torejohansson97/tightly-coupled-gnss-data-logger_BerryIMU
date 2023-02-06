# tightly-coupled-gnss-data-logger_BerryIMU

## How to use this ROS node

### Init the directory
	mkdir ~/catkin_ws
	cd catkin_ws
	git clone URL ./src
	cd ~/catkin_ws/src
	git submodule init
	git submodule update
	cd ~/catkin_ws
	catkin_make


### Build the RTIMULib
	cd ~/catkin_ws/src/RTIMULib2/Linux
	mkdir build
	cd build
	cmake ..
	make -j4
	make install
	ldconfig


### Copy the RTIMUConfig
	cp ~/catkin_ws/src/BerryIMU/RTIMULib.ini ~/catkin_ws/

### (Run the ROS Node localy)
	cd ~/catkin_ws
	source devel/setup.bash
	rosrun BerryIMU BerryIMU_node
