

//==========================================================================================================================================
// This is a function that allows us to follow a line at a speed and for a number of rotations
// It uses a PID controller.
//==============================================================================================================================
// input speed, distance, side of line, color sensor
// side of line ---  1 = left side;  2 = right side
// color sensor -- 1 = left color sensor;  2 = right color sensor

void lineFollowRotations(float speed, float rotations, int sideOfLine, int colorSensor, bool brakeMode)
{

	float setpoint;
	float Kp;
	float Ki;
	float Kd;
	float colorSensorCurrentReading;

	float error;
	float lastError;
	float integral;
	float derivative;

	float correctionAmount;
	float leftMotorSpeed;
	float rightMotorSpeed;
	int numberOfEncoderUnitsToMove;

	// Computing the constants
	// 	Kc = .5 - This is the proportional gain that when used along makes the robot oscitlate.
	// 	Pc = Oscillation Period  = .4 - Tjis is the time it takes to oscilate when proportional gain is set to the critical.
	// 	dT = 50ms = .025 - THis is controlled by the sleep in the program - This is the time for the program to run.

	// Kp = 0.60 * Kc = .3
	// Ki = 2KpdT / Pc = 2 * .3 * .025 / .4 = .0375
	// Kd = KpPc / (8dT) = .3 * .4 / (8 * .025) = .6

	// Set the value of the middle of the line
	setpoint = 27.5;

	// Set the gain (amount we want to correct by)
	Kp = 0.3;							// This corrected fasted enough
	Ki = 0.0;							// This is turned off - It was makings things wors and didn't need faster correct
	Kd = 0.6;							// This prevented overshoot well

	error = 0.0;
	lastError = 0.0;
	integral = 0.0;
	derivative  = 0.0;


	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	// Determine the number of encoder units to move    units = rotations * 360
	numberOfEncoderUnitsToMove = rotations * 360;

	// Reset the encoder on the left motor
	nMotorEncoder[leftMotor] = 0;

	// Continue until the left motor encoder is greater than the number of encoder units to move
	while (nMotorEncoder[leftMotor] < numberOfEncoderUnitsToMove)
	{
		// if colorsensor 1, which is left color sensor
		if (colorSensor == 1)
		{
			colorSensorCurrentReading = getColorReflected(leftSensor);
		}
		else
		{
			colorSensorCurrentReading = getColorReflected(rightSensor);
		}

		// Compute the error
		error = colorSensorCurrentReading - setpoint;


		// Compute the integral error - This is the running sum of the error
		integral = integral + error;

		// Reset the integral total component when the error value changes signs
		if ((error >= 0.0 && lastError <= 0.0) + (error <= 0.0 && lastError >= 0.0))
		{
			integral = 0.0;		// Zero the integral if the error changed from positive to negative
		}

		// Compute the derivative value - This is the rate of change of the error
		derivative = error - lastError;


		// Compute the correction amount
		correctionAmount = Kp*error + Ki*integral + Kd*derivative;


		// Compute the motor speeds
		// If following left side of line
		if (sideOfLine == 1)
		{
			leftMotorSpeed = speed - correctionAmount;
			rightMotorSpeed = speed + correctionAmount;

		}
		// else - were following the right side of the line
		else
		{
			leftMotorSpeed = speed + correctionAmount;
			rightMotorSpeed = speed - correctionAmount;
		}

		// Set the motor speeds
		setMotorSpeed(leftMotor, leftMotorSpeed);
		setMotorSpeed(rightMotor, rightMotorSpeed);

		// Set the last error equal to the current error
		lastError = error;

		// Sleep for 50ms
		sleep(25);


	}

	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);

}




//==========================================================================================================================================
// This is a function that allows us to move for a partiuclar speed until we see a line with the other sensor
//==============================================================================================================================
// Speed - Speed to travel
// sideOfLine - 1 = Left Side; 2 = Right Side
// colorSensorToFollowLine - 1 = Left Sensor;  2 = Right Sensor
// colorSensorToFindLine - 1 = Left Sensor;  2 = Right Sensor
// typeOfLineToFind - 1 = White and then black  2 = white
// brakeMOde - True = Brakes on;  False = Brakes Off
//==============================================================================================================================
void lineFollowUntilLine(int speed, int sideOfLine, int colorSensorToFollowLine, int colorSensorToFindLine, int typeOfLineToFind, bool brakeMode)
{

	float setpoint;
	float Kp;
	float Ki;
	float Kd;
	float colorSensorCurrentReadingForFollowing;

	float error;
	float lastError;
	float integral;
	float derivative;

	float correctionAmount;
	float leftMotorSpeed;
	float rightMotorSpeed;

	float valueForWhite;
	float valueForBlack;
	float colorSensorCurrentReadingForLine;

	bool foundWhite;
	bool foundBlack;
	bool foundLine;


	// Set the initial values for found white and black and the check to end the while loop
	foundWhite = false;
	foundBlack = false;
	foundLine = false;


	valueForWhite = 47;
	valueForBlack = 7;

	// Computing the constants
	// 	Kc = .5 - This is the proportional gain that when used along makes the robot oscitlate.
	// 	Pc = Oscillation Period  = .4 - Tjis is the time it takes to oscilate when proportional gain is set to the critical.
	// 	dT = 50ms = .025 - THis is controlled by the sleep in the program - This is the time for the program to run.

	// Kp = 0.60 * Kc = .3
	// Ki = 2KpdT / Pc = 2 * .3 * .025 / .4 = .0375
	// Kd = KpPc / (8dT) = .3 * .4 / (8 * .025) = .6

	// Set the value of the middle of the line
	setpoint = 27;

	// Set the gain (amount we want to correct by)
	Kp = 0.3;							// This corrected fasted enough
	Ki = 0.0;							// This is turned off - It was makings things wors and didn't need faster correct
	Kd = 0.6;							// This prevented overshoot well

	error = 0.0;
	lastError = 0.0;
	integral = 0.0;
	derivative  = 0.0;

	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	// Get the initial value of the color sensor to check for line.
	if (colorSensorToFindLine == 1)
	{
		colorSensorCurrentReadingForLine = getColorReflected(leftSensor);
	}
	else
	{
		colorSensorCurrentReadingForLine = getColorReflected(rightSensor);
	}




	// Continue until we find white
	while (!(foundLine))
	{
		// if colorsensor 1, which is left color sensor
		if (colorSensorToFollowLine == 1)
		{
			colorSensorCurrentReadingForFollowing = getColorReflected(leftSensor);
		}
		else
		{
			colorSensorCurrentReadingForFollowing = getColorReflected(rightSensor);
		}

		// Compute the error
		error = colorSensorCurrentReadingForFollowing - setpoint;


		// Compute the integral error - This is the running sum of the error
		integral = integral + error;

		// Reset the integral total component when the error value changes signs
		if ((error >= 0.0 && lastError <= 0.0) + (error <= 0.0 && lastError >= 0.0))
		{
			integral = 0.0;		// Zero the integral if the error changed from positive to negative
		}

		// Compute the derivative value - This is the rate of change of the error
		derivative = error - lastError;


		// Compute the correction amount
		correctionAmount = Kp*error + Ki*integral + Kd*derivative;


		// Compute the motor speeds
		// If following left side of line
		if (sideOfLine == 1)
		{
			leftMotorSpeed = speed - correctionAmount;
			rightMotorSpeed = speed + correctionAmount;

		}
		// else - were following the right side of the line
		else
		{
			leftMotorSpeed = speed + correctionAmount;
			rightMotorSpeed = speed - correctionAmount;
		}

		// Set the motor speeds
		setMotorSpeed(leftMotor, leftMotorSpeed);
		setMotorSpeed(rightMotor, rightMotorSpeed);

		// Set the last error equal to the current error
		lastError = error;

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


