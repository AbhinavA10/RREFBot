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
		motor[MOTOR_AXIAL] = -20;
		// moves up for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION >=distanceDown*(-1)){}
		motor[MOTOR_AXIAL] = 0;
	}
		// moving up
	else{
		motor[MOTOR_AXIAL] = 20;
		// moves down for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION <= distanceDown){}
		motor[MOTOR_AXIAL] = 0;
	}
}
void moveNextRow(){
	nMotorEncoder[MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 30;
	// move to the left most column
	while(nMotorEncoder[MOTOR_BELT] <=SWEEP_CONVERSION*10){}

	motor[MOTOR_BELT] = 0;
	// moving then row down one
	moveRobotDown(13,true);
}

void moveRight(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT]/SWEEP_CONVERSION >= (-1)*dist){}
	motor[MOTOR_BELT] = 0;
}

void moveLeft(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while(nMotorEncoder[MOTOR_BELT] < dist*SWEEP_CONVERSION){}
	motor[MOTOR_BELT] = 0;
}

void placePen (bool setPen)
{
	motor[MOTOR_PEN] = 0;

	if (setPen == 0)
	{
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_FORWARD;
		while (nMotorEncoder [MOTOR_PEN] < 60)
		{}
	}
	else
	{
		nMotorEncoder [MOTOR_PEN] = 0;
		motor[MOTOR_PEN] = PEN_SPEED_BACKWARD;
		while (nMotorEncoder [MOTOR_PEN] > -60)
		{}
	}

	motor[MOTOR_PEN] = 0;
}
void writeZero()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(8, true);
	moveLeft(3);
	moveRobotDown(8, false);
	placePen(0);
}

void writeOne()
{

	moveRight(1.5);
	placePen(1);
	moveRobotDown(8, true);
	placePen(0);
	moveLeft(1.5);
	moveRobotDown(8, false);
}

void writeTwo()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(4, true);
	moveLeft(3);
	moveRobotDown(4, true);
	moveRight(3);
	placePen(0);
	// move up 8
	moveRobotDown(8, false);
	moveLeft(3);
}

void writeThree()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(4, true);
	moveLeft(3);
	placePen(0);
	moveRight(3);
	placePen(1);
	moveRobotDown(4, true);
	moveLeft(3);
	placePen(0);
	// move up
	moveRobotDown(8, false);
}

void writeFour()
{
	placePen(1);
	moveRobotDown(4, true);
	moveRight(3);
	moveRobotDown(4, true);
	moveRobotDown(8, false);
	placePen(0);
	moveLeft(3);
}

void writeFive()
{
	placePen(1);
	moveRight(3);
	moveLeft(3);
	moveRobotDown(4, true);
	moveRight(3);
	moveRobotDown(4, true);
	moveLeft(3);
	placePen(0);
	// move up
	moveRobotDown(8, false);
}

void writeSix()
{
	placePen(1);
	moveRight(3);
	moveLeft(3);
	moveRobotDown(4, true);
	moveRight(3);
	moveRobotDown(4, true);
	moveLeft(3);
	moveRobotDown(4, false);
	placePen(0);
	moveRobotDown(4, false);
}

void writeSeven()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(8, true);
	placePen(0);
	moveLeft(3);
	moveRobotDown(8, false);
}

void writeEight()
{
	placePen (1);
	moveRight(3);
	moveRobotDown (4, true);
	moveLeft(3);
	moveRobotDown (4, true);
	moveRight(3);
	moveRobotDown (4, false);
	moveLeft(3);
	moveRobotDown (4, false);
	placePen (0);
}

void writeNine()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(8, true);
	placePen(0);
	moveLeft(3);
	moveRobotDown(4, 0);
	placePen(1);
	moveRight(3);
	moveLeft(3);
	moveRobotDown(4, false);
	placePen(0);
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
/*
task main(){
	placePen(0);
	outputWrite(4);
	moveRight(5);
	outputWrite(5);
	moveRight(5);
	outputWrite(6);
	moveNextRow();
	outputWrite(7);
	moveRight(5);

}
*/

// for MAIN PROGRAM BELOW
int arraySolved[2][3] = {{7,8,9},{1,4,6}};
void writeSolvedMatrix(){
		for (int index = 0; index < 2; index++)
	{
		for (int count = 0; count < 3; count++)
		{
			outputWrite(arraySolved[index][count]);
			moveRight(5);
		}
		moveNextRow();
	}

}
task main(){
writeSolvedMatrix();
}
