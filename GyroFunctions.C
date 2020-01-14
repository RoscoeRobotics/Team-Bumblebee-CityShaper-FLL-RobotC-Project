//==========================================================================================================================================
// This is a function that will recalibrate the gryoscope
//==============================================================================================================================
void recalibrateGyroscope()
{

	// Force the controller to think the gyroscope is a touch sensor and wait 5 seconds for this to work
	SensorType[S2] = sensorEV3_Touch;
	wait1Msec(5000);

	// Now reset it back to a gyro sensor to force a recalibration.   Wait five seconds for this to work.
	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(5000);

}
//=====================================================================================================
// This is a function that will display the gryoscope value
//=====================================================================================================
void displayGyro()
{

	displayBigTextLine(1, "Gyro: %d", getGyroDegrees(Gyroscope));


}
