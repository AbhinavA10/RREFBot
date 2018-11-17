const tMotor MOTOR_PEN = motorA;
const tMotor MOTOR_ARM = motorB;
const int PEN_SPEED_FORWARD = 20;
const int PEN_SPEED_BACKWARD = -20;

void outputWrite (int value)
{
	motor[MOTOR_PEN] = 0;
	nMotorEncoder [MOTOR_PEN] = 0;
	motor[MOTOR_PEN] = PEN_SPEED_FORWARD;
	while (nMotorEncoder [MOTOR_PEN] < 90)
	{}
	motor[MOTOR_PEN] = 0;	

	if (value == 0)
		writeZero();
	else if (value == 1)
		writeOne();
	else if (value == 2)
		writeTwo();
	else if (value == 3)
		writeThree();
	else if (value == 4)
		writeFour();
	else if (value == 5)
		writeFive();
	else if (value == 6)
		writeSix();
	else if (value == 7)
		writeSeven();
	else if (value == 8)
		writeEight();
	else // value = 9
		writeNine();
	
	nMotorEncoder [MOTOR_PEN] = 0;
	
	motor[MOTOR_PEN] = PEN_SPEED_BACKWARD;
	
	while (nMotorEncoder [MOTOR_PEN] > 0)
	{}
	
	motor[MOTOR_PEN] = 0;
}

void writeZero ();
{
	motor[MOTOR]
	nMotorEncoder [MOTOR_ARM] = 0;
	
}

float getAngleToMove(int distance){
	return (distance - 8.444505466*pow(10, -1))/2.995578422*pow(10,-1);
}
float getSweepDistance(int angle)
{
    // after modelling the data as
    return 2.995578422*pow(10,-1)*angle + 8.444505466*pow(10, -1);
}