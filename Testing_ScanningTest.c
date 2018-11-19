const int AXIAL_CONVERSION = 180/(2.75*PI);
const float SWEEP_CONVERSION = 180/(0.725*PI);

const float HEIGHT = 1.1;
const float WIDTH = 1.1;
const int ROW_NUM=9;
const int COL_NUM=5;

const int AXIAL = motorC;
const int SWEEPER = motorB;
const int COLOR_SENS=S2;

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

void nextPixelRight(){
	motor[SWEEPER]=-30;
	nMotorEncoder[SWEEPER]=0;
	while(nMotorEncoder[SWEEPER] >= (-1)*WIDTH*SWEEP_CONVERSION){}
	motor[SWEEPER]=0;
}
void nextLineDown(){
	motor[AXIAL]=30;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[AXIAL]/AXIAL_CONVERSION <= HEIGHT){}
	motor[AXIAL]=0;
}


void goFullyLeft(){
	motor[SWEEPER]=50;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[SWEEPER] < 15*WIDTH*SWEEP_CONVERSION){}
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
task main()
{
	SensorType[COLOR_SENS] = sensorEV3_Color;
	wait1Msec(10);
	SensorMode[COLOR_SENS] = modeEV3Color_Reflected;
	wait1Msec(10);

	bool scan = 0;

	for(int row=0; row < 20; row++){
		for(int col=0; col < 15; col++){
			// determine black or white
			if(SensorValue[COLOR_SENS] > 30)
				scan = 0;
			else
				scan = 1;

			// store in first digit
			if(col<5 && row<9)
				Digit1[row][col]=scan;
			// store in second digit
			else if(col>=5 && col<10 && row<9)
				Digit2[row][col-5]=scan;
			// store in third digit
			else if(col>=10 && row<9)
				Digit3[row][col-10]=scan;
			// store in 4th digit
			else if(col<5 && row>11)
				Digit4[row-12][col]=scan;
			// 5th
			else if(col>=5 && col<10 && row>11)
				Digit5[row-12][col-5]=scan;
			// 6th
			else
				Digit6[row-12][col-10]=scan;

			nextPixelRight();
			wait1Msec(500);
		}

		goFullyLeft();
		nextLineDown();
		wait1Msec(1000);
	}
	outputMatrx();
	wait1Msec(2000);
}
