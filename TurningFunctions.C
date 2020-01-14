//==============================================================================================================================
// This function will be used to turn the robot until it finds a white and then black line
//==============================================================================================================================
// colorSensor -  1 = Left;  2 = Right
// leftOrRight -  1 = Left;  2 = Right;  All Others = error
// sideOrCenterTurn - 1 = Side; 2 = Center; All OTher = Error
//==============================================================================================================================
void turnWhiteBlack(int colorSensor, int leftOrRight, int sideOrCenterTurn, bool brakeMode)
{

	float colorSensorCurrentReading;
	float valueForWhite;
	float valueForBlack;
	int turnRatio;
	int motorSpeed;

	// Set the motor speed
	motorSpeed = 20;

	// Set the value for the white line
	valueForWhite = 45.0;

	// Set the value for black
	valueForBlack = 15.0;


	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	// Get the right turn ratio
	if (sideOrCenterTurn == 1) 	// This is a side turn
	{
		if (leftOrRight == 1) //Check which way to turn
		{
			turnRatio = 50;
		}
		else                  //
		{
			turnRatio = -50;
		}
	}
	else												// Assume this is a center turn for anything besides 1
	{
		if (leftOrRight == 1)
		{
			turnRatio = 100;
		}
		else
		{
			turnRatio = -100;
		}

	}


	// Get the current Reading
	if (colorSensor == 1)
	{
		colorSensorCurrentReading = getColorReflected(leftSensor);
	}
	else
	{
		colorSensorCurrentReading = getColorReflected(rightSensor);
	}

	// Check for white
	while (colorSensorCurrentReading < valueForWhite)
	{

		// Turn on the motors
		setMotorSync(leftMotor, rightMotor, turnRatio, motorSpeed);

		if (colorSensor == 1)
		{
			colorSensorCurrentReading = getColorReflected(leftSensor);
		}
		else
		{
			colorSensorCurrentReading = getColorReflected(rightSensor);
		}

	}

	// Check for black
	while (colorSensorCurrentReading > valueForBlack)
	{

		// Turn off the motors
		setMotorSync(leftMotor, rightMotor, turnRatio, motorSpeed);

		if (colorSensor == 1)
		{
			colorSensorCurrentReading = getColorReflected(leftSensor);
		}
		else
		{
			colorSensorCurrentReading = getColorReflected(rightSensor);
		}

	}


	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);

}


//==============================================================================================================================
// This function will be used to turn the robot using the gyroscope a certain number of degrees.
//==============================================================================================================================
// Speed -  THis works forward or backwards - Negative is backwards
// leftOrRight -  1 = Left;  2 = Right;  All Others = error
// sideOrCenterTurn - 1 = Side; 2 = Center; All OTher = Error
// degreesToTurn - The number of degrees to turn
// Relative or absolute position - Relative = 1; Absolute = 2
// Brake Mode - True or False
//==============================================================================================================================
void gyroTurn(int speed, int leftOrRight, int sideOrCenterTurn, float degreesToTurn, int relativeOrAbsolute, bool brakeMode)
{

	float gyroStartHeading;						// Heading when starting
	float gyroCurrentReading;
	float preActionDegrees;

	int turnRatio;
	int motorSpeed;

	gyroCurrentReading = getGyroDegrees(Gyroscope);
	preActionDegrees = 10;

	// relative is 1
	if (relativeOrAbsolute == 1)
			gyroStartHeading = gyroCurrentReading;

	// absolute is 2
	if (relativeOrAbsolute == 2)
			gyroStartHeading = 0;

	// Set the turn ratio for the motor command
	// 100 applies power to nMotorOne and negative power to nMotorTwo.
	// -100 applies negative power to nMotorOne and power to nMotorTwo.
	// 50 applies all of the power to nMotorOne and zero power to nMotorTwo.
	// -50 applies zero power to nMotorOne and all of the power to nMotorTwo.

	if (sideOrCenterTurn == 1) 	// This is a side turn
	{

		if ((leftOrRight == 1 && speed > 0) || (leftOrRight == 2 && speed < 0)) 	//Check for a left turn
		{
			turnRatio = 50;
		}
		else                  //
		{
			turnRatio = -50;
		}
	}
	else												// Assume this is a center turn for anything besides 1
	{

		if ((leftOrRight == 1 && speed > 0) || (leftOrRight == 2 && speed < 0))  // CHeck for a right turn
		{
			turnRatio = 100;
		}
		else
		{
			turnRatio = -100;
		}

	}


	// Set the motors to coast to remove the brakes
	setBrakeMode(false);


	// Set the motor speed
	motorSpeed = speed;


	// Turn on the motors
	setMotorSync(leftMotor, rightMotor, turnRatio, motorSpeed);


	if (leftOrRight == 1) 			// Turning left - gyroscope goes negative
	{
			// Wait until the robots moves a number of encoder units
		while ((-degreesToTurn + preActionDegrees) <= (gyroCurrentReading - gyroStartHeading))
		{
			gyroCurrentReading = getGyroDegrees(Gyroscope);
			displayGyro();
			wait1Msec(1);
		}
	}
	else												// Turning right - gyroscope goes positive
	{

			// Wait until the robots moves a number of encoder units
		while ((degreesToTurn - preActionDegrees) >= (gyroCurrentReading - gyroStartHeading))
		{
			gyroCurrentReading = getGyroDegrees(Gyroscope);
			displayGyro();
			wait1Msec(1);
		}

	}



	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);


	// Set the proper brake Mode
	setBrakeMode(brakeMode);





}



//==============================================================================================================================
// This function will be used to turn the robot using rotations
//==============================================================================================================================
// leftOrRight -  1 = Left;  2 = Right;  All Others = error
// sideOrCenterTurn - 1 = Side; 2 = Center; All OTher = Error
// degreesToTurn - The number of degrees of the robot to turn.
//==============================================================================================================================
void encoderTurn(int leftOrRight, int sideOrCenterTurn, float degreesToTurn, bool brakeMode)
{

	long leftMotorEncoderCurrentValue;					// Variable to hold the number of current encoder units
	long rightMotorEncoderCurrentValue;					// Variable to hold the number of current encoder units

	long motorNumberOfEncoderUnitsToMove;		// Number of units to move
	int turnRatio;
	int motorSpeed;

	// Set the turn ratio for the motor command
	// 100 applies power to nMotorOne and negative power to nMotorTwo.
	// -100 applies negative power to nMotorOne and power to nMotorTwo.
	// 50 applies all of the power to nMotorOne and zero power to nMotorTwo.
	// -50 applies zero power to nMotorOne and all of the power to nMotorTwo.

	if (sideOrCenterTurn == 1) 	// This is a side turn
	{

		 // decrease preact
		degreesToTurn = degreesToTurn - 6;

		// set the number of encoder units to move
		motorNumberOfEncoderUnitsToMove = degreesToTurn * 3.333333333333333333333333;

		if (leftOrRight == 1) //Check which way to turn
		{
			turnRatio = 50;
		}
		else                  //
		{
			turnRatio = -50;
		}
	}
	else												// Assume this is a center turn for anything besides 1
	{


		// set the number of encoder units to move
		motorNumberOfEncoderUnitsToMove = degreesToTurn * 1.666666666666666666666666666;

		if (leftOrRight == 1)
		{
			turnRatio = 100;
		}
		else
		{
			turnRatio = -100;
		}

	}


	// Set the motors to coast to remove the brakes
	setBrakeMode(false);


	// Set the motor speed
	motorSpeed = 25;

	// Reset the motor encoder
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];
	rightMotorEncoderCurrentValue = nMotorEncoder[rightMotor];

	// Turn on the motors
	setMotorSync(leftMotor, rightMotor, turnRatio, motorSpeed);

	// Wait until the robots moves a number of encoder units
	while ((leftMotorEncoderCurrentValue < motorNumberOfEncoderUnitsToMove) && (rightMotorEncoderCurrentValue < motorNumberOfEncoderUnitsToMove))
	{
		// Get the value of the encoder
		leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];
		rightMotorEncoderCurrentValue = nMotorEncoder[rightMotor];

	}


	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);


	// Set the proper brake Mode
	setBrakeMode(brakeMode);


}
