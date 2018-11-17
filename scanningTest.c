const float DIST_CONV=180/(2.75*PI);

const int AXIAL = motorB;
const int SWEEPER = motorA;
const int COLOR_SENS=S2;

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

float getSweepDistance(int angle){
	// after modelling the data as
	return (2.995578422*0.1*angle + 8.444505466*0.1);
}
int getAngleToMove(int distance){
    return (int)(distance - 8.444505466*0.1)/(2.995578422*0.1);
}

void nextPixel(){
	motor[SWEEPER]=70;
	nMotorEncoder[SWEEPER]=0;
	while(getSweepDistance(nMotorEncoder[SWEEPER]) < WIDTH){}
	motor[SWEEPER]=0;
}
void nextLine(){
	motor[AXIAL]=20;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[AXIAL]/DIST_CONV < HEIGHT){}
	motor[SWEEPER]=0;
}
void goLeft(){
	motor[SWEEPER]=-50;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[AXIAL] > (-1)*ANGLE_SPAN){}
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
			nextPixel(); // horizontal
			wait1Msec(1000);
		}
		nextLine();
		wait1Msec(1000);
	}
	outputMatrix();
}
