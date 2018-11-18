const int BACK_WHEELS = motorB;
const int SWEEPER = motorA;
const int COLOR_SENS=S2;
const float WHEEL_RADIUS = 2.75

const float WIDTH = 1.5; // x distance between each pixel
const float HEIGHT = 0.75;
const int ANGLE_SPAN = 90; // range of the arm for the robot

const int PX_WIDTH=15;
const int PX_HEIGHT=20;

bool Digit1[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};
bool Digit2[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};
bool Digit3[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};
bool Digit4[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};
bool Digit5[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};
bool Digit6[9][5] = {
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0}	};

float getEncCountFromWheelDist(float distance){
	return distance * (180.0/(WHEEL_RADIUS*PI));
}
float getWheelDistFromEncCount(double count){
	return count / (180.0/(WHEEL_RADIUS*PI));
}


void nextPixelRight(){
	motor[SWEEPER]=70;
	nMotorEncoder[SWEEPER]=0;
	// insert function too convert wheel rope to linear distance
	motor[SWEEPER]=0;
}
void nextPixelLeft(){
	motor[SWEEPER]=-70;
	nMotorEncoder[SWEEPER]=0;
	// range of angle thing
	//goes from 0.844 to 1.5
	while(getSweepDistance(nMotorEncoder[SWEEPER]) > 0.844-1.5){}
	motor[SWEEPER]=0;
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

void goLeft(){
	motor[SWEEPER]=-50;
	nMotorEncoder[SWEEPER]=0;
	while(nMotorEncoder[SWEEPER] > (-1)*ANGLE_SPAN){}
	motor[SWEEPER]=0;
}
void outputMatrix(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit1[i][0], Digit1[i][1], Digit1[i][2], Digit1[i][3], Digit1[i][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
task main(){
	SensorType[COLOR_SENS]= sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOR_SENS]= modeEV3Color_Reflected;
	wait1Msec(50);
	bool isBlack=false;
	for(int row=0; row < PX_HEIGHT; row++){
		for(int column=0; column < PX_WIDTH; column++){
			isBlack = false;
			if (SensorValue[COLOR_SENS] < 30)
				isBlack = true;
			if (row<9){
				if(column<5){
					Digit1[row][column]=isBlack;
				}
				else if(column>=5 && column<10){
					Digit2[row][column-5]=isBlack;
				}
				else if(column>=10){
					Digit3[row][column-10]=isBlack;
				}
			}
			else if (row>11){
				if(column<5){
					Digit4[row][column]=isBlack;
				}
				if(column>=5 && column<10){
					Digit5[row][column-5]=isBlack;
				}
				if(column>=10){
					Digit6[row][column-10]=isBlack;
				}
			}
			//nextPixelRight(); // horizontal

			nextPixelLeft(); // horizontal
			wait1Msec(1000);
		}
		moveRobotDown(HEIGHT, 1);
		wait1Msec(1000);
	}
	outputMatrix();
}
