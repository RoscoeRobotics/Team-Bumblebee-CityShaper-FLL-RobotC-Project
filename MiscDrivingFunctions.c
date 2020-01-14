void setMotorsToCoast()
{
	setMotorBrakeMode(leftMotor,motorCoast);
	setMotorBrakeMode(rightMotor,motorCoast);
	setMotorBrakeMode(frontAttachment,motorCoast);
	setMotorBrakeMode(backAttachment,motorCoast);
}


void resetMotorEncoders()
{
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[frontAttachment] = 0;
	nMotorEncoder[backAttachment] = 0;
}




//==========================================================================================================================================
// Name: setBrakeMode
//==============================================================================================================================
// Description: Turns the brakes on the motor on and off
//==============================================================================================================================
// Inputs:
//	brakeMode = True or false depdending on if you want to the brake on or off
//==============================================================================================================================
// Outputs:
//  none
//==============================================================================================================================
void setBrakeMode(bool brakeMode)
{

	if (brakeMode)
	{
		// Set the brakes on the drive motors
		setMotorBrakeMode(leftMotor, motorBrake);
		setMotorBrakeMode(rightMotor, motorBrake);
	}
	else
	{
		// Set the motors to coast
		setMotorBrakeMode(leftMotor,motorCoast);
		setMotorBrakeMode(rightMotor,motorCoast);
	}


}



//==========================================================================================================================================
// Name: driveForTime
//==============================================================================================================================
// Description: drive for the specified number of milisecons
//==============================================================================================================================
// Inputs:
//	leftSpeed = Speed of left motor
//	rightSpeed = Speed of right motor
// 	Time = Milliseconds to drive
//==============================================================================================================================
// Outputs:
//  none
//==============================================================================================================================
void driveForTime(int leftSpeed, int rightSpeed, int milisecconds)
{
// go for 3 secconds (3000 milisecconds) when jamming into crane
	setMotorSpeed(leftMotor, leftSpeed);
	setMotorSpeed(rightMotor, rightSpeed);
  sleep(milisecconds);
  setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
}


//==========================================================================================================================================
// Name: cleanWheels
//==============================================================================================================================
// Description: Turns the wheels on for 20s to clean the wheels
//==============================================================================================================================
// Inputs:
//	none
//==============================================================================================================================
// Outputs:
//  none
//==============================================================================================================================
void cleanWheels()
{
	driveForTime(100, 100, 20000);
}
