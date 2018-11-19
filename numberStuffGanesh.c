// fixing this file currently
const int MOTOR_PEN = motorA;
const int MOTOR_BELT = motorB;
const int MOTOR_AXIAL = motorC;
const int PEN_SPEED_FORWARD = 5;
const int PEN_SPEED_BACKWARD = -5;
const int AXIAL_CONVERSION = 180/(2.75*PI);
const float SWEEP_CONVERSION = 180/(0.575*PI);

void moveRobotDown(int distanceDown, bool down){
	nMotorEncoder[MOTOR_AXIAL] = 0;
	if(down){
		motor[MOTOR_AXIAL] = 10;
		// moves down for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION <= distanceDown){}
		motor[MOTOR_AXIAL] = 0;
	}
		// moving up
	else{
		motor[MOTOR_AXIAL] = -10;
		// moves up for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION >=distanceDown*(-1)){}
		motor[MOTOR_AXIAL] = 0;
	}
}

void placePen (bool setPen)
{
	motor[MOTOR_PEN] = 0;

	if (setPen == 0)
	{
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_FORWARD;
		while (nMotorEncoder [MOTOR_PEN] < 65)
		{}
	}
	else
	{
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_BACKWARD;
		while (nMotorEncoder [MOTOR_PEN] > -65)
		{}
	}

	motor[MOTOR_PEN] = 0;
}

int getAngleToMove(int distance){
    return (int)(distance - 8.444505466*0.1)/(2.995578422*0.1);
}

void writeZero ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 0);
}

void writeOne ()
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(1.5))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (1);

	moveRobotDown (8, 1);

	placePen (0);

	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(1.5))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 0);
}

void writeTwo ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 0);
}

void writeThree ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (1);

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (0);

	moveRobotDown (8, 0);
}

void writeFour ()
{
	placePen(1);

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	moveRobotDown (8, 0);

	placePen(0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;
}

void writeFive ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (0);

	moveRobotDown (8, 0);
}

void writeSix ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 0);
}

void writeSeven ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 1);

	placePen (0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (8, 0);
}
void moveLeft();
void moveRight();
void writeEight ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT]/SWEEP_CONVERSION >= (-1)*3)
	{}
	//moves belt right
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, true);
	// moves down 4cm

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	//moves belt left
	while(nMotorEncoder[MOTOR_BELT] < 3*SWEEP_CONVERSION)
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, true);
	//moves robot down 4

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	//moves belt right
	while (nMotorEncoder[MOTOR_BELT]/SWEEP_CONVERSION >= (-1)*3)
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, false);
	//moves up
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while(nMotorEncoder[MOTOR_BELT] < 3*SWEEP_CONVERSION)
	{}
// moves left
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, false);
	// moves up
	placePen (0);
}

void writeNine ()
{
	placePen (1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 1);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while (nMotorEncoder[MOTOR_BELT] < getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	placePen (1);

	moveRobotDown (4, 1);

	placePen (0);

	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT] > -getAngleToMove(3))
	{}
	motor[MOTOR_BELT] = 0;

	moveRobotDown (4, 0);

	placePen (1);

	moveRobotDown (4, 0);
}

void outputWrite (int value)
{
	if (value == 0)
	{
		writeZero();
	}
	else if (value == 1)
	{
		writeOne();
	}
	else if (value == 2)
	{
		writeTwo();
	}
	else if (value == 3)
	{
		writeThree();
	}
	else if (value == 4)
	{
		writeFour();
	}
	else if (value == 5)
	{
		writeFive();
	}
	else if (value == 6)
	{
		writeSix();
	}
	else if (value == 7)
	{
		writeSeven();
	}
	else if (value == 8)
	{
		writeEight();
	}
	else // value = 9
	{
		writeNine();
	}
}
task main(){
placePen(0);
outputWrite(8);
}
