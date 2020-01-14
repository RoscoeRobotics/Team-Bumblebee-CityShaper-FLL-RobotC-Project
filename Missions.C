
void treeMission()
{
	// Wait a half second before starting to rest after the button press
	sleep(500);

	// Reset gyroscope
	resetGyro(Gyroscope);

	//Drive forward using the gyro to get the back in the right place to turn
	driveStrightGyroRotations(30, 0.5, 0, true);

	//Turn using the gyro to aim towards the black line
	gyroTurn(15, 2, 1, 50, 2, false);

	//Drive forward using the gyro to find line
	driveStrightGyroRotations(30, 1.75, 50, true);

	//Line follow until we get to the end of the line
	lineFollowRotations(10, 0.8, 1, 2, false);

	// Reset gyroscope
	resetGyro(Gyroscope);

	//get into a known position at the line
	driveStraightGyroUntilLine(10, 1, 0, 2, true);

	//backup to get in the correct spot for the lowering
	driveStraightRotations(-7, 0.2, false, true);

	//let the lowering commence!
	moveFrontAttachment(60, 1500);

	//backup to get the innovative architecture in the right place
	driveRotations(-10, -10, 0.35, false);

	// Raise the back arm to release the innovative architecture into the circle (SERVE DINNER!!!)
	moveBackAttachment(60, 600);

	// Raise the front arm to clear the innovative architecture as we drive back
	moveFrontAttachment(-60, 200);

	//backup to get the back corner of the robot in the correct place for turning
	driveRotations(-60, -60, 2, false);

	//turn to aim towards home
	gyroTurn(30, 2, 2, 40, 1, true);

	//backup to get into home
	driveRotations(-50, -50, 2.8, false);

	//center turn to get completely in home
	driveRotations(30, -30, 0.35, false);

}




void eastMission()
{

	// Wait a half second before starting to rest after the button press
	sleep(500);

	// Reset gyroscope
	resetGyro(Gyroscope);

	//moveFrontAttachment(80,500);

	// drive straight using the encoders at 60% power, for 1 rotation, with a speed accel/decel ramp (true), and no brakes(false)
	driveStraightRotations(60, 0.75, true, false	);

	// Turn 90 degrees
	gyroTurn(20, 2, 1, 90, 1, true);

	// get on the line
	driveStraightRotations(40, 1, true, false	);

	// Turn 15 degrees to avoid other colors on the mat
	//gyroTurn(20, 2, 1, 15, 1, false);

	// Turn to find the white and black line and brake so we don't go over the line
	//turnWhiteBlack(2, 2, 1, true);

	// Line follow slowly to not loose the line easily.
	lineFollowRotations(10, 0.25, 1, 2, false);

	// Line follow until were close to the where the line zig zags
	lineFollowRotations(30, 2, 1, 2, false);

	// Use the gyroscope to drive at 90 degrees until we see the line
	driveStraightGyroUntilLine(30, 1, 90.0, 1, false);

	// use the gyro the drive forward a bit to get back on the line.
	driveStrightGyroRotations(30, .15, 90.0, false);

	// line follow for roations to stay on the line
	lineFollowRotations(15, 1.1, 1, 2, true);

	// Lower the arm to get in position to knock down the swing
	moveFrontAttachment(80,800);

	// Drive forward to release swing
	lineFollowRotations(15, 0.2, 1, 2, true);

	// Backup to get the arm in the right place
	driveRotations(-10, -10, 0.2, true);

	//raise the arm to get it into position to knock down the beams
	moveFrontAttachment(-80, 1730);

	// Go straight a bit to get in position to knock down the beams
	lineFollowRotations(15, 0.35, 1, 2, false);

	// Turn to the right to knock down the beams
	gyroTurn(30, 2, 1, 20, 1, true);

	// Wait a half second to settle
	sleep (500);

	// Turn to the left to get in a good position to backup
	gyroTurn(30, 1, 1, 18, 1, true);

	// Backup to clear the back left beam
	driveRotations(-10, -10, 0.05, true);

	// Turn to the left to knock down the beam to the left
	gyroTurn(30, 1, 1, 25, 1, true);

	//raise the arm to get it out of the way
	moveFrontAttachment(80, 850);

	// Turn to prepare to backup towards the city shaper logo
	gyroTurn(20, 2, 2, 50, 1, false);

	// Backup towards the city shaper logo
	driveRotations(-20, -20, 1.5, false);

	// Turn to avoid the city shaper logo
	gyroTurn(20, 1, 1, 30, 1, false);

	// Turn until we see white and then black
	turnWhiteBlack(1, 1, 1, false);

	// Turn to get on the other side of the line
	gyroTurn(10, 1, 2, 20, 1, true);

	//lower the arm to prepare to knock into the buiding see-saw
	moveFrontAttachment(-80, 300);

	// Line follow with the left sensor on the left edge to knock over see-saw
	lineFollowRotations(10, 0.5, 1, 1, true);

	// Line follow with the left sensor on the left edge to knock over see-saw
	lineFollowRotations(25, 0.75, 1, 1, true);

	//raise the arm to get it out of the way
	moveFrontAttachment(80, 550);

	// Go straight a little more
	driveRotations(10, 10, 0.25, true);

	// Turn a little to avoid the blue sticks
	gyroTurn(15, 1, 1, 30, 1, true);

	// Go straight a little more
	driveRotations(10, 10, 0.5, true);

	// Turn a little more
	gyroTurn(15, 1, 1, 35, 1, true);

	// Go straight a little more
	driveRotations(10, 10, 0.1, true);

	// Turn a litte more
	gyroTurn(15, 1, 1, 15, 1, false);

	// Lower the arm to prepare to lift building
	moveFrontAttachment(-80, 1100);

	// Drive forward to pick up building
	driveRotations(10, 10, 0.4, false);

	// Raise the arm to lift the building
	moveFrontAttachment(100, 1200);

	// Turn to bring the building all the way up
	gyroTurn(10, 2, 2, 20, 1, false);

	// Drive backwards to clear the building
	driveRotations(-10, -10, 0.4, false);

}



void craneMission()
{

	// Reset gyroscope
	resetGyro(Gyroscope);

	// Drive Straight Using the Gyroscope
	 driveStrightGyroRotations(15, 0.2, 0, false);

	//Turn using rotations right (2), side Turn (1), 20 degrees, relative turn without brakes)
	 gyroTurn(15, 2, 1, 40, 1, false);

	// Drive Straight Using the Gyroscope to get the back corner of the robot in the right place
	 driveStrightGyroRotations(15 , 0.32, 32, false);

	//Turn back so we are facing forward
	 gyroTurn(15, 1, 1, 40, 1, false);

	//drive forward to get the color sensor on the line
	driveStrightGyroRotations(10 , .1, 0, false);

	//drive forward to get the color sensor on the line
	driveStrightGyroRotations(20 , .2, 0, false);

	//drive forward to get the color sensor on the line
	driveStrightGyroRotations(35 , 1.2, 0, true);

	//Line follow at 10% power on the right side of the line using color sensor 1 until we see white black with color sensor 2(20, 2, 1, 2, 1, true)
	 lineFollowUntilLine(10, 2, 1, 2, 2, true);

	driveStraightRotations(10, 0.25, false, false);

	driveForTime(4,4,1000);

	sleep(1000);

	repeat(4)
	{
		moveFrontAttachment(-50,200);
		sleep(300);
		moveFrontAttachment(50,200);
	}

	// Drive backwards after the block is dropped
	driveRotations(-50, -50, 2.5, false);

	// Gyro turn 85 degrees
	gyroTurn(-40, 2, 1, 75, 1, false);

	// Drive backwards
	driveRotations(-80, -80, 2.3, false);

	// Gyro turn 90 degrees
	gyroTurn(-50, 1, 2, 80, 1, true);

}



void pushMission()
{

	resetGyro(Gyroscope);

	//push the buildings out at a max speed of 30 for 1 rotation using the ramp
	driveStrightGyroRotations(20, 0.25, 0, false);

	driveStrightGyroRotations(60, 2.1, 0, true);

	// backup to clear the buildings
	driveRotations(-80, -80, 2, false);

	// Gyro turn 90 degrees
	gyroTurn(-50, 2, 1, 90, 2, false);

	// aim towards home
	driveRotations(-70, -70, 1.5, false);

	// Gyro turn 90 degrees
	gyroTurn(-50, 1, 2, 90, 1, true);


}

void finalMission()
{
	// Wait a half second
	delay(500);

	// Reset gyroscope
	resetGyro(Gyroscope);

	//driveRotations(13,55,.2,false);

	driveRotations(13, 15, 0.4,false);

	driveRotations(23, 25, 0.2,false);

	driveRotations(40, 50, 1.4,false);

	driveRotations(30, 35, 0.65,true);

	delay (500);

	gyroTurn(15, 1, 2, 90, 1, true);

	driveStrightGyroRotations(20, .8, -90, true);

	gyroTurn(15, 2, 1, 80, 1, true);

	turnWhiteBlack(2, 2, 1, true);

	// Line follow slowly to not loose the line easily.
	lineFollowRotations(15, 0.85, 1, 2, false);

	// release the red blocks
	moveFrontAttachment(-100, 300);

	// Follow the line a bit
	lineFollowRotations(20, .5, 1, 2, false);

	// Use the gyroscope to drive at 90 degrees until we see the line
	driveStraightGyroUntilLine(20, 1, 0, 1, true);

	driveStrightGyroRotations(10, 0.25, 0, true);

	// Follow the line a bit
	lineFollowRotations(20, 0.55, 1, 2, true);

	// Turn to aim towards ramp
	gyroTurn(-20, 2, 1, 63, 1, true);

	// Drive back to release the tan blocks
	driveStrightGyroRotations(-30, 1.8, 59, true);

	// release the tan blocks
	moveFrontAttachment(-100, 300);

	// Drive up the ramp
	driveStrightGyroRotations(-60, 4.3, 62, true);

}
