#include "PC_FileIO.c"

string fileName="Numbers.txt";

const int AXIAL_CONVERSION = 180/(2.75*PI);// DO NOT CHANGE
const float SWEEP_CONVERSION = 180/(0.725*PI); // DO NOT CHANGE

const float HEIGHT = 1.0;// fix this
const float WIDTH = 1.1;
const int ROW_NUM=9;
const int COL_NUM=5;

const int AXIAL = motorC;
const int MOTOR_AXIAL=AXIAL;
const int SWEEPER = motorB;
const int MOTOR_BELT=SWEEPER;
const int COLOR_SENS=S2;
const int MOTOR_PEN = motorA;
const int PEN_SPEED_FORWARD = 5;
const int PEN_SPEED_BACKWARD = -5;

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

void placePen (bool setPen);
void moveLeft(int dist);
void moveRight(int dist);
void moveNextRow();
void moveRobotDown(int distanceDown, bool down);
void writeZero();
void writeOne();
void writeTwo();
void writeThree();
void writeFour();
void writeFive();
void writeSix();
void writeSeven();
void writeEight();
void writeNine();
void outputWrite(int value);
void writeSolvedMatrix();

void computeMatrix();
void reduceSecondEntries();
void reduceFirstEntries();
void reduceSingleRow(int row, int coloumn);
void swap2Rows(int row1, int row2);
void subtract2rows(int multiplier, int rowToFix, int rowToUse);


task main()
{
	TFileHandle fin;
	bool fileOkay=openReadPC(fin,fileName);

	SensorType[COLOR_SENS] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOR_SENS] = modeEV3Color_Reflected;
	wait1Msec(50);
	const int SOUND_SENSOR = S1;
	// configure sound sensors
	SensorType[SOUND_SENSOR] = sensorSoundDB;
	// we used the automatic robotc thing to generate name of legacy nxt sensor
	wait1Msec(50);
	bool begin = false;
	// dont start until someone starts yelling
	while(SensorValue[SOUND_SENSOR]<90){}
 	clearTimer(T1);
 	while(SensorValue[SOUND_SENSOR] >70&&!begin){
 		// if they have been yelling for 3 seconds
 		if(time1[T1]>1000){
 		 begin = true;
 		}
	}

	if(begin){
			//write REST OF MAIN HERE =========
	//START SCANNING
		bool scan = 0;

		for(int row=0; row < 20; row++){
			for(int col=0; col <15; col++){
				// determine black or white
				if(SensorValue[COLOR_SENS] < 10){
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
				wait1Msec(50);

				if (col==14){
					if(SensorValue[COLOR_SENS] <10){
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
		wait1Msec(15000);
		computeMatrix();
		eraseDisplay();
		outputMatrix();
		wait1Msec(15000);
		eraseDisplay();

		for (int index = 0; index < 2; index++){
				for (int count = 0; count < 3; count++){
				if (matrix[index][count] >=10){
					int sum = matrix[index][count] - 10;
					matrix[index][count] -= sum+1;
					// We need to
					// this is only in case our scan doesn't have a positive solution
			}

				if (matrix[index][count] <0){
					matrix[index][count]*=-1 ; // output something in case we didn't get a positive solution
					// this is only in case our scan doesn't have a positive solution
					}
				}
		}
		writeSolvedMatrix();
		}
		else{
				//Sets the sound volume of the EV3 speaker to 75
			setSoundVolume(75);
			// Starts playing a soundfile, 'Bravo.rsf' on the EV3
			playSound(soundDownwardTones);
			sleep(3000);
		}


}
// =======================END OF TASK MAIN=======================
// =======================END OF TASK MAIN=======================
// =======================END OF TASK MAIN=======================
// =======================END OF TASK MAIN=======================
// =======================END OF TASK MAIN=======================
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
	while(nMotorEncoder[SWEEPER] < 16*WIDTH*SWEEP_CONVERSION){}
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

//================Writing stuff=====================
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
	while(nMotorEncoder[MOTOR_BELT] <=SWEEP_CONVERSION*15){}

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
void outputWrite(int value)
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

void writeSolvedMatrix(){
		for (int index = 0; index < 2; index++)
	{
		for (int count = 0; count < 3; count++)
		{
			outputWrite(matrix[index][count]);
			moveRight(5);
		}
		moveNextRow();
	}

}

// ========================RREF+=================================


// ==================================== SUBTRACT 2 ROWS ===================

void subtract2rows(int multiplier, int rowToFix, int rowToUse){

	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are using to fix the rowToFix

	for (int j =0; j<3;j++){ // jth coloumn. is this okay?

		matrix[rowToFix][j] = matrix[rowToFix][j] - multiplier*matrix[rowToUse][j];

	}

}

// ==================================== SWAP 2 ROWS ===================

// even more useful function in R3

void swap2Rows(int row1, int row2){

	for (int j =0; j<3;j++){

		int temp = matrix[row1][j];

		matrix[row1][j] = matrix[row2][j];

		matrix[row2][j] = temp;

	}

}

// ==================================== REDUCE SINGLE ROW ===================

void reduceSingleRow(int row, int coloumn){

	int multiplier = matrix[row][coloumn];

	for (int j =0; j<3;j++){

		matrix[row][j] = matrix[row][j]/multiplier; // since whole number unique solution

	}

}

// ==================================== SWAP 2 ROWS ===================

void reduceFirstEntries(){

	// if this is called, it means it is not of the form [1

	//													  0] in the first coloumn

		if (matrix[0][0]>matrix[1][0]){ // if coloumn 1 first row's entry is bigger than second row's entry

			if (matrix[1][0]==0){ // if second entry is 0

				reduceSingleRow(1,0); // need to reduce just the first row, using the 1st entry

			}

			else if (matrix[0][0]-matrix[1][0]==1){

				 // difference is only positive 1, therefore,

				subtract2rows(1,0,1);// subtract small (second) row from big (first) row

			}

			else{ // some random stuff

				//row 1 = row 1 -2row2

				subtract2rows(matrix[0][0]/matrix[1][0], 0, 1);

			}

		}

		else if (matrix[0][0]<matrix[1][0]){ // if second row's colomun 1 entries are bigger

			swap2Rows(0,1); // easy way to deal with it

		}

		else{ // if equal

			subtract2rows(1,1,0);



		}

}

void reduceSecondEntries(){

	// if this is called, it means it is not of the form [1

	//													  0] in the second coloumn

	// but we know that it is (1,0)T in the first coloumn. That means we only need to reduce the second row coloumn

	// and get rid of the entry in the first row second coloumn. Therefore,

	if (matrix[1][1]!=1){

		reduceSingleRow(1,1); // reduce second row using 2nd entry in 2nd row

	}

	else{

		subtract2rows(matrix[0][1],0,1);

	}

}

void computeMatrix(){

	// add check for inconsistency

	/*

if ( (matrix[0][0] == 0 && matrix[1][0] == 0 ) || (matrix[0][1] == 0 && matrix[1][1] == 0 ) ){

	cout <<"Error: system incosistent" << endl;

}

	*/

	while ((matrix[0][0]!=1 || matrix[1][0]!=0 || matrix[0][1]!=0 || matrix[1][1]!=1)&& !(( (matrix[0][0] == 0 && matrix[1][0] == 0 ) || (matrix[0][1] == 0 && matrix[1][1] == 0 ) ))){ // while not in rref

		if (matrix[0][0]!=1 || matrix[1][0]!=0 ){

			reduceFirstEntries();}

		else{ // at this point, the first coloumn is proper

			reduceSecondEntries();

		}

		outputMatrix();

		wait1Msec(500);

	}
	if ( (matrix[0][0] == 0 && matrix[1][0] == 0 ) || (matrix[0][1] == 0 && matrix[1][1] == 0 )){
			//Sets the sound volume of the EV3 speaker to 75
			setSoundVolume(75);
			// Starts playing a soundfile, 'Bravo.rsf' on the EV3
			playSound(soundDownwardTones);
			sleep(3000);
			displayBigTextLine(1,"incosistent");
	}
		outputMatrix();

	wait1Msec(4000);

}
