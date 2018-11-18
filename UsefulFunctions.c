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

float getEncCountForWheelDist(float distance){
	return distance * (180.0/(WHEEL_RADIUS*PI));
}
float getWheelDistFromEncCount(double count){
	return count / (180.0/(WHEEL_RADIUS*PI));
}

float getBeltDistFromEncCount(double count){
	return count / (180.0/(BELT_PULLY_RADIUS*PI));
}
float getEncCountForBeltDistance(double distance){
	return distance * (180.0/(BELT_PULLY_RADIUS*PI));
}

void goFullyLeft(){
	motor[MOTOR_BELT]=50;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT] < getEncCountForBeltDistance(23)){}
	motor[MOTOR_BELT]=0;
}
void nextPixelRight(){
	// assuming starting at left side, move sensor one unit right (1.5)
	motor[MOTOR_BELT]=-70;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT]>=-getEncCountForBeltDistance(WIDTH)){} // this might be wrong
	motor[MOTOR_BELT]=0;
}
void moveRobotDown(int distanceDown, bool down){
	nMotorEncoder[BACK_WHEELS] = 0;
	if(down){
		motor[BACK_WHEELS] = 10;
		// moves down for specified distance
		while(nMotorEncoder[BACK_WHEELS]<=(getEncCountFromWheelDist(distanceDown))){}
		motor[BACK_WHEELS] = 0;
	}
		// moving up
	else{
		motor[BACK_WHEELS] = -10;
		// moves down for specified distance
		while(nMotorEncoder[BACK_WHEELS]>=((getEncCountFromWheelDist(distanceDown)))*-1){}
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