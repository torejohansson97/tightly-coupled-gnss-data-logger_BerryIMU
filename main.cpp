#include "../RTIMULib2/RTIMULib/RTIMULib.h"
#include "../RTIMUBerryGPS-IMUV4/RTIMUBerryIMU.h"

int main(){
	int samleCount = 0;
	int sampleRate = 0;
	uint64_t rateTimer;
	uint64_t displayTimer;
	uint64_t now;

	RTIMUSettings *settings = new RTIMUSettings("BerryGPS-IMU");

	RTIMU *imu = RTIMU::createIMU(settings);

	if((imu == NULL) || (imu->IMUtype() == RTIMU_TYPE_NULL)){
		printf("No IMU found\n");
		exit(1);
	}

	imu->IMUInit();
}
