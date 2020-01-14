

//==========================================================================================================================================
// This is a function that allows us to move for a partiuclar speed and for a number of rotations
//==============================================================================================================================
void driveStraightRotations(float speed, float rotations, bool ramp, bool brakeMode)
{
	long leftMotorEncoderCurrentValue;					// Variable to hold the number of current encoder units
	long leftMotorNumberOfEncoderUnitsToMove;		// Number of units to move
	long rampEncoderDistance;										// Distance the motor traveled during the ramp period
	int motorSetpointSpeed;											// Motor setpoint speed
	int motorRampSpeedIncrement;								// Amount to increase speed by
	int motorRampTimeIncrement;									// Amount of time to wait between speed ramps
	int motorMinSpeed;													// Minimum speed of the motor during deceleration

	// Increment the speed by 10 every half second
	motorRampSpeedIncrement = 10;								// Set Speed increment
	motorRampTimeIncrement = 200;								// Set time increment
	motorMinSpeed = 10;													// Set the motor minimum speed on the ramp

	// Multiple the number of rotations by the number of encoder units in a rotation
	leftMotorNumberOfEncoderUnitsToMove = rotations * 360;
	rampEncoderDistance = 0;

	// Set the motors to coast to remove the brakes
	setBrakeMode(false);


	// Reset the motor encoder
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];


	// Check if going forward
	if (speed > 0 && rotations > 0)
	{
			// if ramp is not on, then just set the setpoint speed to the speed. else set the starting speed to the initial ramp
			if (!ramp)
				motorSetpointSpeed = speed;
			else
				motorSetpointSpeed = motorRampSpeedIncrement;

			// Synch the left and right motor to go stright
			setMotorSync(leftMotor, rightMotor, 0, motorSetpointSpeed);

			// Reset the time
			clearTimer(T1);

			// This is the while loop that goes until the motor rotations
			while ((leftMotorEncoderCurrentValue ) < leftMotorNumberOfEncoderUnitsToMove - rampEncoderDistance )
			{
				// Check if were not at full speed and greater than time has passed to increse ramp speed
				if ((motorSetpointSpeed < speed) && (time1[T1]> motorRampTimeIncrement))
				{
					motorSetpointSpeed = motorSetpointSpeed + motorRampSpeedIncrement;

					// Check if this is the last speed increase because were at or over speed
					if (motorSetpointSpeed >= speed)
					{
						motorSetpointSpeed = speed;
						rampEncoderDistance = nMotorEncoder[leftMotor] - 150;
					}
					clearTimer(T1);

					// Set the motor speeds
					setMotorSync(leftMotor, rightMotor, 0, motorSetpointSpeed);
				}

				// Get the value of the encoder
				leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];
			}

			// Check to see if we need to decelerate with a ramp.
			if (ramp)
			{
				// Reset the time
				clearTimer(T1);

				// This is the while loop that goes until the motor rotations
				while ((leftMotorEncoderCurrentValue) < leftMotorNumberOfEncoderUnitsToMove)
				{
					// Check if were not at full speed and greater than time has passed to increse ramp speed
					if ((speed > motorMinSpeed) && (time1[T1]> motorRampTimeIncrement))
					{
						motorSetpointSpeed = motorSetpointSpeed - motorRampSpeedIncrement;

						// Check if this if we set the speed too low
						if (motorSetpointSpeed < motorMinSpeed)
						{
							motorSetpointSpeed = motorMinSpeed;
						}

						clearTimer(T1);

						setMotorSync(leftMotor, rightMotor, 0, motorSetpointSpeed);

					}

					// Get the value of the encoder
					leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];
				}
			}
	}
	else						// Were going backwards
	{

		// Make sure the speed is negative
		if (speed > 0) speed = -speed;

		// Always make sure rotations are negative
		if (leftMotorNumberOfEncoderUnitsToMove > 0) leftMotorNumberOfEncoderUnitsToMove = -leftMotorNumberOfEncoderUnitsToMove;


		// Synch the left and right motor to go stright
		setMotorSync(leftMotor, rightMotor, 0, speed);


		while (leftMotorEncoderCurrentValue >= leftMotorNumberOfEncoderUnitsToMove)
		{

				// Get the value of the encoder
				leftMotorEncoderCurrentValue = nMotorEncoder[leftMotor];

		}

	}

	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);


	return;

}




//==========================================================================================================================================
// This is a function that allows us to move for a partiuclar speed and for a number of rotations
//==============================================================================================================================
void driveRotations(float leftSpeed, float rightSpeed, float rotations, bool brakeMode)
{

	long MotorEncoderCurrentValue;					// Variable to hold the number of current encoder units
	long MotorNumberOfEncoderUnitsToMove;		// Number of units to move

	bool usingLeftOrRight;				// Left = True; Right = False


	// Multiple the number of rotations by the number of encoder units in a rotation
	MotorNumberOfEncoderUnitsToMove = rotations * 360;

	// Set the motors to coast to remove the brakes
	setBrakeMode(false);

	// Reset the motor encoder
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;

	usingLeftOrRight = false;

	// Check which encoder to use to determine travel
	if (abs(leftSpeed) > abs(rightSpeed)) usingLeftOrRight = true;


	// Check which speed is greater and then use that motor as the encoder value
	if (usingLeftOrRight)
	{
			MotorEncoderCurrentValue = nMotorEncoder[leftMotor];
	}
	else
	{
			MotorEncoderCurrentValue = nMotorEncoder[rightMotor];
	}


	// Check if going forward
	if ((usingLeftOrRight && leftSpeed > 0) || (!usingLeftOrRight && rightSpeed > 0) )
	{
			setMotorSpeed(leftMotor, leftSpeed);
		  setMotorSpeed(rightMotor, rightSpeed);

			// This is the while loop that goes until the motor rotations
			while (MotorEncoderCurrentValue < MotorNumberOfEncoderUnitsToMove)
			{

				// Get the encoder value for the cortrect encoder
				if (usingLeftOrRight)
				{
						MotorEncoderCurrentValue = nMotorEncoder[leftMotor];
				}
				else
				{
						MotorEncoderCurrentValue = nMotorEncoder[rightMotor];
				}

			}

	}

	else						// We're going backwards
	{

		// Always make sure rotations are negative
		if (MotorNumberOfEncoderUnitsToMove > 0) MotorNumberOfEncoderUnitsToMove = -MotorNumberOfEncoderUnitsToMove;

		setMotorSpeed(leftMotor, leftSpeed);
		setMotorSpeed(rightMotor, rightSpeed);


		while (MotorEncoderCurrentValue >= MotorNumberOfEncoderUnitsToMove)
		{

				// Get the encoder value for the cortrect encoder
				if (usingLeftOrRight)
				{
						MotorEncoderCurrentValue = nMotorEncoder[leftMotor];
				}
				else
				{
						MotorEncoderCurrentValue = nMotorEncoder[rightMotor];
				}


		}

	}

	// Stop the left and right drive motors
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// Set the brake mode
	setBrakeMode(brakeMode);


	return;

}
