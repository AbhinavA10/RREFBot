#include "PC_FileIO.c"

string fileName="Numbers.txt";

const int AXIAL_CONVERSION = 180/(2.75*PI);// DO NOT CHANGE
const float SWEEP_CONVERSION = 180/(0.725*PI); // DO NOT CHANGE

const float HEIGHT = 0.9;// fix this
const float WIDTH = 1.1;
const int ROW_NUM=9;
const int COL_NUM=5;

const int AXIAL = motorC;
const int SWEEPER = motorB;
const int COLOR_SENS=S2;

bool Digit1[9][5];
bool Digit2[9][5];
bool Digit3[9][5];
bool Digit4[9][5];
bool Digit5[9][5];
bool Digit6[9][5];

int errorList1[10];
int errorList2[10];
int errorList3[10];
int errorList4[10];
int errorList5[10];
int errorList6[10];

int matrix[2][3];
bool libraryMatrix[9][5];

void nextPixelRight();
void nextLineDown();
void goFullyLeft();

void outputMatrix();
void outputMatrix1();
void outputMatrix2();
void outputMatrix3();
void outputMatrix4();
void outputMatrix5();
void outputMatrix6();

int compareMatrix1();
int compareMatrix2();
int compareMatrix3();
int compareMatrix4();
int compareMatrix5();
int compareMatrix6();

task main()
{
	TFileHandle fin;
	bool fileOkay=openReadPC(fin,fileName);

	SensorType[COLOR_SENS] = sensorEV3_Color;
	wait1Msec(10);
	SensorMode[COLOR_SENS] = modeEV3Color_Reflected;
	wait1Msec(10);
//START SCANNING
	bool scan = 0;

	for(int row=0; row < 20; row++){
		for(int col=0; col <15; col++){
			// determine black or white
			if(SensorValue[COLOR_SENS] == 0){
				scan = 1;
			}
			else{
				scan = 0;
			}
			// store in first digit
			if(col<5 && row<9)
				Digit1[row][col]=scan;
			// store in second digit
			else if(col>=5 && col<10 && row<9)
				Digit2[row][col-5]=scan;
			// store in third digit
			else if(col>=10 && col<15 && row<9)
				Digit3[row][col-10]=scan;
			// store in 4th digit
			else if(col<5 && row>11)
				Digit4[row-12][col]=scan;
			// 5th
			else if(col>=5 && col<10 && row>11)
				Digit5[row-12][col-5]=scan;
			// 6th
			else  if(col>=10 && col<15 && row>11)
				Digit6[row-12][col-10]=scan;
			nextPixelRight();
			if (col==14){
				if(SensorValue[COLOR_SENS] ==0){
					scan = 1;
				}
				else{
					scan = 0;
				}
				if(row<9)
					Digit3[row][col-10]=scan;
				else if(row>11)
					Digit6[row-12][col-10]=scan;
			}
		}
		goFullyLeft();
		nextLineDown();
	}
	int value = 0;
	for(int number=0; number<10; number++){

		// populates an array using text file

		for(int i=0; i<9; i++){

			for(int j=0; j<5; j++){

				readIntPC(fin, value);

				libraryMatrix[i][j] = value;

			}

		}
		// fill a list with number of errors between each matrix

		errorList1[number] = compareMatrix1();
		errorList2[number] = compareMatrix2();
		errorList3[number] = compareMatrix3();
		errorList4[number] = compareMatrix4();
		errorList5[number] = compareMatrix5();
		errorList6[number] = compareMatrix6();
	}

	// 1rd digit estimation
	int smallestError1=45;
	int bestEstimate1=0;
	int smallestError2=45;
	int bestEstimate2=0;
	int smallestError3=45;
	int bestEstimate3=0;
	int smallestError4=45;
	int bestEstimate4=0;
	int smallestError5=45;
	int bestEstimate5=0;
	int smallestError6=45;
	int bestEstimate6=0;

	for(int index=0; index<9; index++){
		if(errorList1[index] < smallestError1){
			smallestError1 = errorList1[index];
			matrix[0][0] = index;
		}
		if(errorList2[index] < smallestError2){
			smallestError2 = errorList2[index];
			matrix[0][1] = index;
		}
		if(errorList3[index] < smallestError3){
			smallestError3 = errorList3[index];
			matrix[0][2] = index;
		}
		if(errorList4[index] < smallestError4){
			smallestError4 = errorList4[index];
			matrix[1][0] = index;
		}
		if(errorList5[index] < smallestError5){
			smallestError5 = errorList5[index];
			matrix[1][1] = index;
		}
		if(errorList6[index] < smallestError6){
			smallestError6 = errorList6[index];
			matrix[1][2] = index;
		}
	}

	outputMatrix();
	wait1Msec(5000);
	eraseDisplay();
}

void nextPixelRight(){
	motor[SWEEPER]=-30;
	nMotorEncoder[SWEEPER]=0;
	while(nMotorEncoder[SWEEPER] >= (-1)*WIDTH*SWEEP_CONVERSION){}
	motor[SWEEPER]=0;
}
void nextLineDown(){
	motor[AXIAL]=-30;
	nMotorEncoder[AXIAL]=0;
	while(nMotorEncoder[AXIAL] >= (-1)*HEIGHT*AXIAL_CONVERSION){}
	motor[AXIAL]=0;
}

void goFullyLeft(){
	motor[SWEEPER]=50;
	nMotorEncoder[SWEEPER]=0;
	while(nMotorEncoder[SWEEPER] <= 15*WIDTH*SWEEP_CONVERSION){}
	motor[SWEEPER]=0;
}

void outputMatrix1(){

	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit1[i][0], Digit1[i][1], Digit1[i][2], Digit1[i][3], Digit1[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}

void outputMatrix2(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit2[i][0], Digit2[i][1], Digit2[i][2], Digit2[i][3], Digit2[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}
void outputMatrix3(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit3[i][0], Digit3[i][1], Digit3[i][2], Digit3[i][3], Digit3[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}

void outputMatrix4(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit4[i][0], Digit4[i][1], Digit4[i][2], Digit4[i][3], Digit4[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}
void outputMatrix5(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit5[i][0], Digit5[i][1], Digit5[i][2], Digit5[i][3], Digit5[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}
void outputMatrix6(){
	int lineNum =0;
	for (int i=0;i<9; i++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", Digit6[i][0], Digit6[i][1], Digit6[i][2], Digit6[i][3], Digit6[i][4]);
		lineNum++;
	}
	wait1Msec(5000);

}

int compareMatrix1(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit1[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
int compareMatrix2(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit2[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
int compareMatrix3(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit3[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
int compareMatrix4(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit4[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
int compareMatrix5(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit5[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
int compareMatrix6(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(Digit6[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}

void outputMatrix(){
	int lineNum =0;
	for (int i=0;i<2; i++){
		displayBigTextLine(lineNum, "   %d  %d  | %d  ", matrix[i][0], matrix[i][1], matrix[i][2]);
		lineNum+=3;

	}

}
