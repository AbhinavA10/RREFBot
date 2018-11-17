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
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};
bool Digit2[9][5] = {
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};
bool Digit3[9][5] = {
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};;
bool Digit4[9][5] = {
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};
bool Digit5[9][5] = {
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};
bool Digit6[9][5] = {
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0},
						{0 0 0 0 0}	};

float getSweepDistance(int angle){
	// after modelling the data as
	return 2.995578422*pow(10,-1)*angle + 8.444505466*pow(10, -1);
}

void nextPixel(){
	motor[SWEEPER]=30;
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

task main(){
	SensorType[COLOR_SENS]= sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOR_SENS]= modeEV3Color_Reflected;
	wait1Msec(50);

// Assumption: the color sensor intensity will be boolean (>1 or 0)
	for(int row=0; row < PX_HEIGHT; row++){
		for(int column=0; column < PX_WIDTH; column++){
			if(column<5 && row<=8){
				Digit1[row][column]=SensorValue[COLOR_SENS];
			}
			else if(column>=5 && column<10 && row<=8){
				Digit2[row][column]=SensorValue[COLOR_SENS];
			}
			else if(column>=10 && row<=8){
				Digit3[row][column]=SensorValue[COLOR_SENS];
			}

			else if(column<5 && row>12 && row<16){
				Digit4[row][column]=SensorValue[COLOR_SENS];
			}
			else if(column>5 && column<=10 && row<16){
				Digit5[row][column]=SensorValue[COLOR_SENS];
			}
			else if(column>10 && row <=16){
				Digit5[row][column]=SensorValue[COLOR_SENS];
			}
			nextPixel();
		}
		nextLine();
	}
}
