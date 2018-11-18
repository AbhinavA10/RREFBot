const int MOTOR_PEN = motorA;
const int MOTOR_ARM = motorB;
const int MOTOR_AXIAL = motorC;
const int PEN_SPEED_FORWARD = 20;
const int PEN_SPEED_BACKWARD = -20;

void placePen (bool setPen)
{
	motor[MOTOR_PEN] = 0;
	
	if (setPen == 0)
	{			
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_FORWARD;
		while (nMotorEncoder [MOTOR_PEN] < 90)
		{}
	}
	else 
	{	
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_BACKWARD;
		while (nMotorEncoder [MOTOR_PEN] > -90)
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
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 0);	
}

void writeOne ()
{
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(1.5))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (1);
	
	moveRobotDown (8, 1);
	
	placePen (0);
	
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(1.5))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 0);	
}

void writeTwo ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 0);
}

void writeThree ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (1);
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (0);
	
	moveRobotDown (8, 0);	
}

writeFour ()
{
	placePen(1);
	
	moveRobotDown (4, 1); 
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	moveRobotDown (8, 0);
	
	placePen(0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;	
}

writeFive ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (0);
	
	moveRobotDown (8, 0);
}

void writeSix ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
		
	moveRobotDown (8, 0);
}

void writeSeven ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 1);
	
	placePen (0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (8, 0);	
}

void writeEight ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 0);
}

void writeNine ()
{
	placePen (1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	moveRobotDown (4, 1);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = 10;	
	while (nMotorEncoder[MOTOR_ARM] < getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
	placePen (1);
	
	moveRobotDown (4, 1);
	
	placePen (0);
	
	motor[MOTOR_ARM] = 0;
	nMotorEncoder [MOTOR_ARM] = 0;
	motor[MOTOR_ARM] = -10;	
	while (nMotorEncoder[MOTOR_ARM] > -getAngleToMove(3))
	{}
	motor[MOTOR_ARM] = 0;
	
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