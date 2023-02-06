#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Vector3Stamped.h>
#include "RTIMULib.h"


int main(int argc, char **argv){
	// ROS setup
	ros::init(argc, argv, "berry_imu");
	ros::NodeHandle n;

	ros::Publisher IMU_pub = n.advertise<sensor_msgs::Imu>("berry/imu/data", 100);
	ros::Publisher MAG_pub = n.advertise<geometry_msgs::Vector3Stamped>("berry/mag", 100);


	// RTIMU setup
	int sampleCount = 0;
	int sampleRate = 0;
	uint64_t rateTimer;
	uint64_t displayTimer;
	uint64_t now;

	RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

	RTIMU *imu = RTIMU::createIMU(settings);

	if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)){
		printf("No IMU found\n");
		exit(1);
	}

	imu->IMUInit();

	imu->setSlerpPower(0.02);
	imu->setGyroEnable(true);
	imu->setAccelEnable(true);
	imu->setCompassEnable(true);
	
	rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();


	ros::Rate loop_rate(100); // 100Hz
	ROS_INFO("Measuring...");
	// Main loop
	while(ros::ok()){
		sensor_msgs::Imu imu_msgs;
		geometry_msgs::Vector3Stamped mag_msgs;
		//now = RTMath::currentUSecsSinceEpoch();

		if(imu->IMURead()){
			RTIMU_DATA imuData = imu->getIMUData();
			RTQuaternion imuQuaternion = imuData.fusionQPose;
			//sampleCount++;

			imu_msgs.linear_acceleration.x = imuData.accel.x();
			imu_msgs.linear_acceleration.y = imuData.accel.y();
			imu_msgs.linear_acceleration.z = imuData.accel.z();

			imu_msgs.angular_velocity.x = imuData.gyro.x();
			imu_msgs.angular_velocity.y = imuData.gyro.y();
			imu_msgs.angular_velocity.z = imuData.gyro.z();

			
			imu_msgs.orientation.w = imuQuaternion.scalar();
			imu_msgs.orientation.x = imuQuaternion.x();
			imu_msgs.orientation.y = imuQuaternion.y();
			imu_msgs.orientation.z = imuQuaternion.z();

			mag_msgs.vector.x = imuData.compass.x();
			mag_msgs.vector.y = imuData.compass.y();
			mag_msgs.vector.z = imuData.compass.z();

			IMU_pub.publish(imu_msgs);
			MAG_pub.publish(mag_msgs);
		}

		/*if(now - rateTimer > 1000000){
			ROS_INFO( "Sample rate: %i", sampleRate);
			sampleRate = sampleCount;
			sampleCount = 0;
			rateTimer = now;
		}*/

		ros::spinOnce();
		loop_rate.sleep();
	}
}
