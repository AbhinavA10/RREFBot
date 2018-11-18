const int AXIAL_CONVERSION = 180/(2.75*PI);
const int SWEEP_CONVERSION = 180/(1.5*PI);

const float HEIGHT = 1;
const float WIDTH = 1.5;
const int ROW_NUM=9;
const int COL_NUM=5;

const int AXIAL = motorB;
const int SWEEPER = motorA;
const int COLOR_SENS=S2;

bool Digit1[ROW_NUM][COL_NUM];
bool Digit2[ROW_NUM][COL_NUM];
bool Digit3[ROW_NUM][COL_NUM];
bool Digit4[ROW_NUM][COL_NUM];
bool Digit5[ROW_NUM][COL_NUM];
bool Digit6[ROW_NUM][COL_NUM];

void nextPixel(){
	motor[SWEEPER]=-30;
	nMotorEncoder[SWEEPER]=0;
	// POSSIBLE ERROR: check that the conversion below is correct
	while(nMotorEncoder[SWEEPER] > WIDTH*AXIAL_CONVERSION*(-1)){}
	motor[SWEEPER]=0;
}
void nextLine(){
	motor[AXIAL]=30;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[AXIAL]/AXIAL_CONVERSION < HEIGHT){}
	motor[SWEEPER]=0;
}


void goLeft(){
	motor[SWEEPER]=50;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[SWEEPER] < 15*WIDTH*SWEEP_CONVERSION){}
	motor[SWEEPER]=0;
}

task main()
{
	SensorType[COLOR_SENS] = sensorEV3_Color;
	wait1Msec(10);
	SensorMode[COLOR_SENS] = modeEV3Color_Reflected;
	wait1Msec(10);

	bool scan = 0;

	for(int row=0; row < ROW_NUM; row++){
		for(int col=0; col < COL_NUM; col++){
			// determine black or white
			if(SensorValue[COLOR_SENS] > 30)
				scan = 0;
			else
				scan = 1;

			// store in first digit
			if(col<5 && row<9)
				Digit1[row][col]=scan;
			// store in second digit
			else if(col>5 && col<10 && row<9)
				Digit2[row-5][col]=scan;
			// store in third digit
			else if(col>10 && row<9)
				Digit3[row-10][col]=scan;
			// store in 4th digit
			else if(col<5 && row>12)
				Digit4[row][col-12]=scan;
			// 5th
			else if(col>5 && col<10 && row>12)
				Digit5[row-5][col-12]=scan;
			// 6th
			else
				Digit6[row-10][col-12]=scan;

			//nextPixel();
		}
		//goLeft();
		//nextLine();
	}
	DisplayString(2, "%d", Digit1[0][0]);
	wait1Msec(2000);
}
