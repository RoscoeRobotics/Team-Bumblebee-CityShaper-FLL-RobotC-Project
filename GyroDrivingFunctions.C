void driveStraightGyroUntilLine(float speed, int colorSensorToFindLine,float degreesSetpoint, int typeOfLineToFind, bool brakeMode)
{

	float Kp;
	float gyroSensorCurrentReading;

	float error;

	float correctionAmount;
	float leftMotorSpeed;
	float rightMotorSpeed;

	float valueForWhite;
	float valueForBlack;
	float colorSensorCurrentReadingForLine;

	bool foundWhite;
	bool foundBlack;
	bool foundLine;

	// Set the initial values for found white and black
	foundWhite = false;
	foundBlack = false;
	foundLine = false;

	valueForWhite = 47;
	valueForBlack = 7;

	// Set the gain (amount we want to correct by)
	Kp = 0.3;							// This corrected fasted enough
	error = 0.0;

	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	gyroSensorCurrentReading = getGyroDegrees(Gyroscope);


	// Get the initial value of the color sensor to check for line.
	if (colorSensorToFindLine == 1)
	{
		colorSensorCurrentReadingForLine = getColorReflected(leftSensor);
	}
	else
	{
		colorSensorCurrentReadingForLine = getColorReflected(rightSensor);
	}


	// Continue until we find the line
	while (!(foundLine))
	{

		gyroSensorCurrentReading = getGyroDegrees(Gyroscope);

		// Compute the error
		error = gyroSensorCurrentReading - degreesSetpoint;

		// Compute the correction amount
		correctionAmount = Kp*error;


		// Compute the motor speeds
			leftMotorSpeed = speed + correctionAmount;
			rightMotorSpeed = speed - correctionAmount;

		// Set the motor speeds
		setMotorSpeed(leftMotor, leftMotorSpeed);
		setMotorSpeed(rightMotor, rightMotorSpeed);

		// Sleep for 50ms
		sleep(25);

		// Read value to check for color sensor to stop
		if (colorSensorToFindLine == 1)
		{
			colorSensorCurrentReadingForLine = getColorReflected(leftSensor);
		}
		else
		{
			colorSensorCurrentReadingForLine = getColorReflected(rightSensor);
		}

		// Check if we have found white
		if (colorSensorCurrentReadingForLine >= valueForWhite)
		{
			foundWhite = true;
		}

		// check for black
		if ((colorSensorCurrentReadingForLine <= valueForBlack) && foundWhite)
		{
			foundBlack = true;
		}


		// If we are following until white then black
		if (typeOfLineToFind == 1)
		{
			foundLine = foundBlack && foundWhite;
		}

		// If we are just finding white
		else
		{
			foundLine = foundWhite;
		}
	}


	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);

}


void driveStrightGyroRotations(float speed, float rotations, float degreesSetpoint, bool brakeMode)
{

	float Kp;
	float gyroSensorCurrentReading;

	float error;

	float correctionAmount;
	float leftMotorSpeed;
	float rightMotorSpeed;
	int numberOfEncoderUnitsToMove;


	// Set the gain (amount we want to correct by)
	Kp = 1.4;							// This corrected fast enough
	error = 0.0;


	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	// Determine the number of encoder units to move    units = rotations * 360
	numberOfEncoderUnitsToMove = rotations * 360;

	gyroSensorCurrentReading = getGyroDegrees(Gyroscope);

	// Reset the encoder on the left motor
	nMotorEncoder[leftMotor] = 0;

	// Continue until the left motor encoder is greater than the number of encoder units to move
	while (abs(nMotorEncoder[leftMotor]) < numberOfEncoderUnitsToMove)
	{

		gyroSensorCurrentReading = getGyroDegrees(Gyroscope);

		// Compute the error
		error = gyroSensorCurrentReading - degreesSetpoint;


		// Compute the correction amount
		correctionAmount = Kp*error;


		// Compute the motor speeds
			leftMotorSpeed = speed + correctionAmount;
			rightMotorSpeed = speed - correctionAmount;

		// Set the motor speeds
		setMotorSpeed(leftMotor, leftMotorSpeed);
		setMotorSpeed(rightMotor, rightMotorSpeed);


		// Sleep for 50ms
		// sleep(25);


	}

	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);



}
