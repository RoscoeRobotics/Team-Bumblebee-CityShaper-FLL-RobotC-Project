
void moveFrontAttachment(int speed, int degrees)
{

	setMotorBrakeMode(frontAttachment,motorCoast );

	moveMotorTarget(frontAttachment, degrees, speed);

	waitUntilMotorStop(frontAttachment);

	setMotorBrakeMode(frontAttachment, motorBrake );


}

void moveBackAttachment(int speed, int degrees)
{

	setMotorBrakeMode(backAttachment,motorCoast );

	moveMotorTarget(backAttachment, degrees, speed);

	waitUntilMotorStop(backAttachment);

	setMotorBrakeMode(backAttachment, motorBrake );


}
