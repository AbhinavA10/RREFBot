const int BACK_WHEELS = motorB;
const int MOTOR_BELT = motorA;
const int COLOR_SENS=S2;
const float WHEEL_RADIUS = 2.75
const float BELT_PULLY_RADIUS = 0.575; // diameter was 1.15 cm

const float WIDTH = 1.5; // x distance between each pixel
const float HEIGHT = 0.75;
const int ANGLE_SPAN = 90; // range of the arm for the robot

const int PX_WIDTH=15;
const int PX_HEIGHT=20;

void moveRobotDown(int distanceDown, bool down){
	nMotorEncoder[BACK_WHEELS] = 0;
	if(down){
		motor[BACK_WHEELS] = 10;
		// moves down for specified distance
		while(nMotorEncoder[BACK_WHEELS]/AXIAL_CONVERSION <= distanceDown){}
		motor[BACK_WHEELS] = 0;
	}
		// moving up
	else{
		motor[BACK_WHEELS] = -10;
		// moves up for specified distance
		while(nMotorEncoder[BACK_WHEELS]/AXIAL_CONVERSION >=distanceDown*(-1)){}
		motor[BACK_WHEELS] = 0;
	}
}
void outputMatrix(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit1[i][0], Digit1[i][1], Digit1[i][2], Digit1[i][3], Digit1[i][4]);
		lineNum++;
	}
	wait1Msec(5000);
}