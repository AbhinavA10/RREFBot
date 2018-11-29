// GROUP 848 -- RREF ROBOT
// TODO replace 9,5,etc. with row_num
// replace i's and j's with acutal variables
/*SOURCES:
	To play built-in sound files:
http://help.robotc.net/WebHelpMindstorms/index.htm#Resources/topics/
LEGO_EV3/ROBOTC/Sounds/playSoundFile.htm
	We learnt what kind of values the NXT sound sensor returns, from:
http://www.legoengineering.com/nxt-sensors/
	We found what the NXT Sound Sensor is referred to as in ROBOTC using the
	"Motor and Sensors Setup" button.
*/
#include "PC_FileIO.c"
// =========================== GLOBAL CONSTANTS =============================
// Note: these constants must be global as they are used throughout the
// many functions that we have created.
const int AXIAL_CONVERSION = 180/(2.75*PI);
// conversion factor for the wheels that move the entire robot
const float SWEEP_CONVERSION = 180/(0.725*PI);
// conversion factor for the gear on the belt that moves the
// colour sensor horizontally. Radius of the gear is 0.725 cm
const float HEIGHT = 1.0; // Height of 1 cell in the printed matrix
const float WIDTH = 1.0; // Width of 1 cell in the printed matrix
const int ROW_NUM=9; // number of rows in 1 section of the printed matrix
const int COL_NUM=5; // number of columns in 1 section of the printed matrix
// Note: the printed matrix is split up into 6 different sections
// one for each digit
const int ROW_NUM_TOTAL = 20; // for the printed matrix
const int COL_NUM_TOTAL = 15; // for the printed matrix
const int ROW_NUM_FINAL = 2; // for the recognized and rref matrix
const int COL_NUM_FINAL = 3;// for the recognized and rref matrix
const int PEN_SPEED_FORWARD = 5; // for the motor that lifts the marker
const int PEN_SPEED_BACKWARD = -5;
const int AXIAL_MOTOR_SPEED = 10; 
// for moving the entire robot forwards and backwards
const int MOTOR_BELT_SPEED = 10; 
// for moving the belt/marker system along left and right along the track
const int ANGLE_PEN = 60; // max angle to lift the pen
const int COLOR_THRESHOLD = 25; //determined by testing the scanning in WEEF lab
const int MOTOR_PEN = motorA;
const int MOTOR_BELT = motorB;
const int MOTOR_AXIAL = motorC;
const int SOUND_SENSOR = S1;
const int COLOR_SENSOR = S2;

// ============================= INITILIAZE ARRAYS ============================
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

int errorList1[10] = {0,0,0,0,0,0,0,0,0,0};
int errorList2[10] = {0,0,0,0,0,0,0,0,0,0};
int errorList3[10] = {0,0,0,0,0,0,0,0,0,0};
int errorList4[10] = {0,0,0,0,0,0,0,0,0,0};
int errorList5[10] = {0,0,0,0,0,0,0,0,0,0};
int errorList6[10] = {0,0,0,0,0,0,0,0,0,0};

bool libraryMatrix[9][5] = {
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0}	};
int matrix[2][3] = {{0, 0, 0},
					{0, 0, 0}}; // the final matrix, used for rref computation

// ============================ FUNCTION PROTOYPES ============================
bool isFrustrated(); // function to check if the user yelled for 2 seconds
// ============================ SCANNING FUNCTIONS ===========================
void nextPixelRight();
void nextLineDown();
void goFullyLeft();
void output2By3Matrix();
void scanMatrix();
// ======================== DIGIT RECOGNITION ===========================
int compareMatrix1();
int compareMatrix2();
int compareMatrix3();
int compareMatrix4();
int compareMatrix5();
int compareMatrix6();
void recognizeDigits();
// ============================ WRITING FUNCTIONS =============================
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
void writeNumber(int value);
void writeSolvedMatrix();

// ============================= DEBUG FUNCTIONS ==============================
// these functions output the raw scan data of each section of the
// printed matrix
void outputMatrix1();
void outputMatrix2();
void outputMatrix3();
void outputMatrix4();
void outputMatrix5();
void outputMatrix6();
// ============================= RREF FUNCTIONS ==============================
void computeMatrix();
void reduceSecondEntries();
void reduceFirstEntries();
void reduceSingleRow(int row, int column);
void swap2Rows(int row1, int row2);
void subtract2rows(int multiplier, int rowToFix, int rowToUse);

// =============================== TASK MAIN  ================================
task main()
{
	SensorType[COLOR_SENSOR] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOR_SENSOR] = modeEV3Color_Reflected;
	wait1Msec(50);
	SensorType[SOUND_SENSOR] = sensorSoundDB;
	// we used the automatic ROBOTC sensor generator to learn the proper name
	// for the "Legacy NXT Sound sensor"
	wait1Msec(50);
	
	bool hasYelledEnough = isFrustrated();

	if(hasYelledEnough){
		scanMatrix();
		recognizeDigits();
		//Outputting the raw data of the scans below
		// useful for debugging
		/*
		outputMatrix1();
		wait1Msec(3000);
		outputMatrix2();
		wait1Msec(3000);
		outputMatrix3();
		wait1Msec(3000);
		outputMatrix4();
		wait1Msec(3000);
		outputMatrix5();
		wait1Msec(3000);
		outputMatrix6();
		wait1Msec(3000);
		*/
		output2By3Matrix();//outputing the recognized matrix
		wait1Msec(15000);
		eraseDisplay();
		computeMatrix(); // taking the matrix to rref
		eraseDisplay();
		output2By3Matrix(); // outputing the rref version on the screen
		wait1Msec(10000);
		for (int index = 0; index < ROW_NUM_FINAL; index++){
			for (int count = 0; count < COL_NUM_FINAL; count++){
				if (matrix[index][count] >= 10){
					int sum = matrix[index][count] - 10;
					matrix[index][count] -= sum+1;
					// this is only in case our scan doesn't have a
					//single digit solution i.e. if it scans improperly
				}
				if (matrix[index][count] < 0){
					matrix[index][count] *= -1 ;
					// output something in case we didn't get a positive
					//solution as we are not able to output negative signs, this
					//is only in case our scan doesn't have a positive solution,
					// to be able to still output some number on the whiteboard
				}
			}
		}
		moveRobotDown(60, false); // move the robot up, away from the scan spot
		writeSolvedMatrix();//outputing the rref of the matrix onto a whiteboard
	}
	else{ // if the user didn't yell for 2 seconds.
		//http://help.robotc.net/WebHelpMindstorms/index.htm#Resources/topics/
		//LEGO_EV3/ROBOTC/Sounds/playSoundFile.htm
		setSoundVolume(100);	//Sets the sound volume of the EV3 speaker
		playSound(soundDownwardTones);
		// Starts playing the built in sound 'soundDownwardTones.rsf' on the EV3
		sleep(3000); // allows time for the robot to play the entire sound file
	}
}
// =========================== END OF TASK MAIN ===============================

// ============================ IS FRUSTRATED  ================================
// This is a function to determine whether the user has yelled in the proper
// manner, required to start the robot
// The values of 90 and 70 used below were found by testing the program
// in a room with ambient noise (E5 Lab)
bool isFrustrated(){
	while(SensorValue[SOUND_SENSOR] < 90){}
	// dont goforward  until someone starts yelling (loud sound)
 	clearTimer(T1);
 	while(SensorValue[SOUND_SENSOR] > 70){
 		if(time1[T1] > 1000){ // if they have been yelling for at least 1 second
 			return true;
 		}
	}
	return false; // indicates user didn't yell for a continous second
	// from when they first started
}
// ============================ NEXT PIXEL RIGHT =============================
// this is a function to move one unit right when scanning the printed matrix
void nextPixelRight(){
	motor[MOTOR_BELT]=-3*MOTOR_BELT_SPEED;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT] >= (int)((-1)*WIDTH*SWEEP_CONVERSION))
	{}
	motor[MOTOR_BELT]=0;
}

// ============================ NEXT LINE DOWN =============================
// This is a function to move the robot one line down when scanning the 
// printed matrix
void nextLineDown(){
	motor[MOTOR_AXIAL]=-3*AXIAL_MOTOR_SPEED;
	nMotorEncoder[MOTOR_AXIAL]=0;
	while(nMotorEncoder[MOTOR_AXIAL] >= (-1)*HEIGHT*AXIAL_CONVERSION)
	{}
	motor[MOTOR_AXIAL]=0;
}
// ============================ GO FULLY LEFT =============================
// this is a function to move from the right end of the track, to the left end
// of the track once the line is done being scanned
void goFullyLeft(){
	motor[MOTOR_BELT]=5*MOTOR_BELT_SPEED;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT] < (int)(16.65*WIDTH*SWEEP_CONVERSION + 0.5))
	{}
	motor[MOTOR_BELT]=0;
}
// ============================ COMPARE MATRIX 1 =============================
/* We need to have these functions below because we can't pass 2D arrays
as paramters in RobotC. Otherwise, we would have passed (int digit [9][5],
int libraryMatrix[9][5]) and compared it by reference.

Each function counts the number of dissimilarities between a scanned section
of a matrix, and a predefined array - "library matrix"
*/
int compareMatrix1(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit1[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ COMPARE MATRIX 2 =============================
int compareMatrix2(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit2[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ COMPARE MATRIX 3 =============================
int compareMatrix3(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit3[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ COMPARE MATRIX 4 =============================
int compareMatrix4(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit4[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ COMPARE MATRIX 5 =============================
int compareMatrix5(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit5[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ COMPARE MATRIX 6 =============================
int compareMatrix6(){
	int errorCount=0;
	for(int rowIndex=0; rowIndex<9; rowIndex++){
		for(int colIndex=0; colIndex<5; colIndex++){
			if(Digit6[rowIndex][colIndex] != libraryMatrix[rowIndex][colIndex]){
				errorCount++;
			}
		}
	}
	return errorCount;
}
// ============================ OUTPUT MATRIX ===============================
void output2By3Matrix(){
	int lineNum = 0;
	for (int row = 0; row < ROW_NUM_FINAL; row++){
		displayBigTextLine(lineNum, "   %d  %d  | %d  ", matrix[row][0],
							matrix[row][1], matrix[row][2]);
		lineNum+=3;
	}
}
// ============================ WRITING FUNCTIONS =============================

// ============================ MOVE ROBOT DOWN ==============================
// this function is to move the robot up/down a specified distance, when writing
// numbers on the white board as we have to move down a certain distance while
// the marker is placed down on the whiteboard.
void moveRobotDown(int distanceDown, bool down){
	nMotorEncoder[MOTOR_AXIAL] = 0;
	if(down){
		motor[MOTOR_AXIAL] = -2*AXIAL_MOTOR_SPEED;
		// moves up for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION >=distanceDown*(-1)){}
		motor[MOTOR_AXIAL] = 0;
	}
		// moving up
	else{
		motor[MOTOR_AXIAL] = 2*AXIAL_MOTOR_SPEED;
		// moves down for specified distance
		while(nMotorEncoder[MOTOR_AXIAL]/AXIAL_CONVERSION <= distanceDown){}
		motor[MOTOR_AXIAL] = 0;
	}
}
// ============================ MOVE NEXT ROW ================================
// function to move to the left end of the track, and then down to the next row
void moveNextRow(){
	nMotorEncoder[MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 3*AXIAL_MOTOR_SPEED;
	// move to the left most column
	while(nMotorEncoder[MOTOR_BELT] <=SWEEP_CONVERSION*15){}

	motor[MOTOR_BELT] = 0;
	// moving then row down one
	moveRobotDown(13,true);
}
// =============================== MOVE RIGHT =================================
// function to move right, a given distance to be able to write a number.
void moveRight(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -MOTOR_BELT_SPEED;
	while (nMotorEncoder[MOTOR_BELT]/SWEEP_CONVERSION >= (-1)*dist){}
	motor[MOTOR_BELT] = 0;
}
// =============================== MOVE LEFT =================================
// similar to the move right function
void moveLeft(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = MOTOR_BELT_SPEED;;
	while(nMotorEncoder[MOTOR_BELT] < dist*SWEEP_CONVERSION){}
	motor[MOTOR_BELT] = 0;
}
// =============================== PLACE PEN =================================
// function to either place the marker on the whiteboard, or pick up the marker
// off the whiteboard, depending on the inputted booleann.
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
// The following are commands to write a given number, using the above functions
// =============================== WRITE ZERO ================================
void writeZero()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(8, true);// move down 8
	moveLeft(3);
	moveRobotDown(8, false); // move up 8
	placePen(0);
}
// =============================== WRITE ONE ================================
void writeOne()
{
	moveRight(1.5);
	placePen(1);
	moveRobotDown(8, true);
	placePen(0);
	moveLeft(1.5);
	moveRobotDown(8, false);
}
// =============================== WRITE TWO ================================
void writeTwo()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(4, true);
	moveLeft(3);
	moveRobotDown(4, true);
	moveRight(3);
	placePen(0);
	moveRobotDown(8, false);
	moveLeft(3);
}
// =============================== WRITE THREE ================================
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
	moveRobotDown(8, false);
}
// =============================== WRITE FOUR ================================
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
// =============================== WRITE FIVE ================================
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
	moveRobotDown(8, false);
}
// =============================== WRITE SIX ================================
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
// =============================== WRITE SEVEN ================================
void writeSeven()
{
	placePen(1);
	moveRight(3);
	moveRobotDown(8, true);
	placePen(0);
	moveLeft(3);
	moveRobotDown(8, false);
}
// =============================== WRITE EIGHT ================================
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
// =============================== WRITE NINE ================================
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
// =============================== OUTPUT WRITE ===============================
// this is a function to make calling the respective write function easier
void writeNumber(int value)
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
// ============================ WRITE SOLVED MATRIX ===========================
// function to loop through the solved matrix, and write the solution
// on the whiteboard in the correct location
void writeSolvedMatrix(){
	for (int index = 0; index < ROW_NUM_FINAL; index++)
	{
		for (int count = 0; count < COL_NUM_FINAL; count++)
		{
			writeNumber(matrix[index][count]);
			moveRight(5);
		}
		moveNextRow();
	}
}

// ========================== RREF FUNCTIONS ==================================
/*
For the following functions:
ERO refers to "Elementry row operation", as defined in Linear Algebra
We are only able to solve 2x3 matricies, that have non-fractional intermediary 
steps. For example, we are not (and did not expect) to be able to an ERO like
R2 - 1/3 * R1 -> R2.

*/
// =========================== SUBTRACT 2 ROWS ===============================
// This is function to subtract multiples of one row, from another.
// Ex. Row2 = Row2-3*Row1
void subtract2rows(int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are
	// using to fix the rowToFix
	for (int colIndex = 0; colIndex< COL_NUM_FINAL; colIndex++){
		matrix[rowToFix][colIndex] = matrix[rowToFix][colIndex] -
								multiplier*matrix[rowToUse][colIndex];
	}
}
// ============================== SWAP 2 ROWS ================================
// This is a function to swap all entries in 2 rows.
void swap2Rows(int row1, int row2){
	for (int colIndex = 0; colIndex< COL_NUM_FINAL; colIndex++){
		int temp = matrix[row1][colIndex];
		matrix[row1][colIndex] = matrix[row2][colIndex];
		matrix[row2][colIndex] = temp;
	}
}
// =========================== REDUCE SINGLE ROW ============================
// This is a function to reduce 1 single row, by dividing each entry in the row
// by a scalar value, which is determined by the 1st entry in the row.
void reduceSingleRow(int row, int column){
	int multiplier = matrix[row][column];
	for (int colIndex = 0; colIndex< COL_NUM_FINAL; colIndex++){
		matrix[row][colIndex] = matrix[row][colIndex]/multiplier; 
		// since whole number unique solution
	}
}
// =========================== REDUCE FIRST ENTRIES ==========================
// This is a function that makes a decision about which of the above functions
// to call based on the current state of the 2 by 3 matrix.
void reduceFirstEntries(){
	// if this is called, it means it is not of the form [1
	//													  0] in the first column
	if (matrix[0][0]>matrix[1][0]){ // if column 1 first row's entry is
									// bigger than second row's entry
		if (matrix[1][0]==0){ // if second entry is 0
			reduceSingleRow(1,0); // need to reduce just the first row,
								  //using the 1st entry
		}
		else if (matrix[0][0]-matrix[1][0]==1){
			 // difference is only positive 1, therefore,
			subtract2rows(1,0,1);// subtract small (second) row from big
								 //(first) row
		}
		else{
			//row 1 = row 1 -2row2
			subtract2rows(matrix[0][0]/matrix[1][0], 0, 1);
		}
	}
	else if (matrix[0][0]<matrix[1][0]){ // if second row's colomun 1
										// entries are bigger
		swap2Rows(0,1); // easy way to fix that
	}
	else{ // if equal
		subtract2rows(1,1,0);
	}
}
// =========================== REDUCE SECOND ENTRIES ==========================
// Similar to the reduceFirstEntries funciton, but this is only called when 
// the first column has been reduced.
void reduceSecondEntries(){
	//if this is called, it means it is not of the form [1
	//													 0] in the second column
	// but we know that it is (1,0)T in the first column. That means we only
	// need to reduce the second row column and get rid of the entry in the
	// first row second column. Therefore,
	if (matrix[1][1]!=1){
		reduceSingleRow(1,1); // reduce second row using 2nd entry in 2nd row
	}
	else{ // if second row's 2nd entry is reduced to 1, then we subtract
		  // multiples of the second row from the first row.
		subtract2rows(matrix[0][1],0,1);
	}
}
// ============================= COMPUTE MATRIX ==============================
// This is a function to carry the 2x3 matrix to RREF
void computeMatrix(){
	while ( (matrix[0][0]!=1||matrix[1][0]!=0||matrix[0][1]!=0||matrix[1][1]!=1)
			// while not in RREF
			&& !(matrix[0][0]==0 && matrix[0][1]==0)
			// and while not a zero row in the top row
			&& !(matrix[1][0]==0 && matrix[1][1]==0) ){ // to avoid divide by 0
			// and while not a zero row in the bottom row
		if (matrix[0][0]!=1 || matrix[1][0]!=0){
			reduceFirstEntries();
		}
		else{ // at this point, the first column is proper rref
			reduceSecondEntries();
		}
		output2By3Matrix();
		wait1Msec(500);
	}
	if ((matrix[1][0] == 0 && matrix[1][1] == 0 && matrix[1][2] != 0)
		||(matrix[0][0] == 0 && matrix[0][1] == 0 && matrix[0][2] != 0) ){
		/* if the rref of the matrix has any row of zeros where the augmented
		   portion (after the line | ) is non-zero, ex. is something like
		   [0 0 | 1] in a row
		   then the system is inconsistent and has no solution
		*/
		setSoundVolume(100);
		playSoundFile("Uh-oh"); // Starts playing a soundfile, on EV3
		sleep(3000);
		eraseDisplay();
		displayBigTextLine(1,"Matrix is");
		displayBigTextLine(3," inconsistent.");
		wait1Msec(2000)
		eraseDisplay();
	}// otherwise, there is at least one solution
	output2By3Matrix(); 
	wait1Msec(4000);
}
// ============================= SCAN MATRIX ==============================
// Function to scan in the printed matrix, and place the current scan value
// in the correct "sectioned" array, depending on the current position of the
// sensor on the track/whiteboard
void scanMatrix(){
	bool isBlack = false;
	for(int row=0; row < 20; row++){
		for(int col=0; col <15; col++){
			// determine black or white
			if(SensorValue[COLOR_SENSOR] < COLOR_THRESHOLD){
				isBlack = true;
			}
			else{
				isBlack = false;
			}
			// store value
			if (row<9){
				if(col<5){
					Digit1[row][col]= isBlack;
				}
				else if(col<10){
					Digit2[row][col-5]= isBlack;
				}
				else{ // 10<=col<15
					Digit3[row][col-10]= isBlack;
				}
			}
			else if (row>11){
				if(col<5){
					Digit4[row-12][col]= isBlack;
				}
				else if(col<10){
					Digit5[row-12][col-5]= isBlack;
				}
				else{ // 10<=col<15
					Digit6[row-12][col-10]= isBlack;
				}
			}
			nextPixelRight(); // move colour sensor right on track to
			// the next cell
			wait1Msec(50);
			// scan again if last column
			if (col == 14){
				if(SensorValue[COLOR_SENSOR] < COLOR_THRESHOLD){
					 isBlack = 1;
				}
				else{
					 isBlack = 0;
				}
				if(row < 9){
					Digit3[row][col-10] = isBlack;
				}
				else if(row > 11){
					Digit6[row-12][col-10] = isBlack;
				}
			}
		}
		goFullyLeft(); // to go all the way back to the starting position
		// on the track (left)
		nextLineDown(); // move the robot down to scan the next line
		//  on the printed matrix
	}
}
// ============================= RECOGNIZE DIGITS ==============================
// Function to determine the numerical value from the sectioned array, by
// comparing to our predefined library
void recognizeDigits(){
	string fileName="Numbers.txt";
	// our text file for the predefined library of scans is "Numbers.txt"
	TFileHandle fin; // we only needed the text file to be accessible
	// in this function, so we decided to reduce the scope of it from main
	bool fileOkay=openReadPC(fin,fileName);
	int value = 0;
	for(int number=0; number<10; number++){
		for(int row=0; row<9; row++){
			for(int col=0; col<5; col++){
				readIntPC(fin, value);
				// populates an array using text file
				libraryMatrix[row][col] = value;
			}
		}
		// fill a list with number of errors between each matrix
		// i.e. the number of dissimilarities between them
		errorList1[number] = compareMatrix1();
		errorList2[number] = compareMatrix2();
		errorList3[number] = compareMatrix3();
		errorList4[number] = compareMatrix4();
		errorList5[number] = compareMatrix5();
		errorList6[number] = compareMatrix6();
	}
	// digit estimation
	// The digit that is the most similar, is estimated to be the value of the 
	// scanned digit
	int smallestError[6] = {45,45,45,45,45,45}; // 45 is the max number of
	// errors: 9x5=45
	for(int index=0; index<9; index++){
		if(errorList1[index] < smallestError[0]){
			smallestError[0] = errorList1[index];
			matrix[0][0] = index;
		}
		if(errorList2[index] < smallestError[1]){
			smallestError[1] = errorList2[index];
			matrix[0][1] = index;
		}
		if(errorList3[index] < smallestError[2]){
			smallestError[2] = errorList3[index];
			matrix[0][2] = index;
		}
		if(errorList4[index] < smallestError[3]){
			smallestError[3] = errorList4[index];
			matrix[1][0] = index;
		}
		if(errorList5[index] < smallestError[4]){
			smallestError[4] = errorList5[index];
			matrix[1][1] = index;
		}
		if(errorList6[index] < smallestError[5]){
			smallestError[5] = errorList6[index];
			matrix[1][2] = index;
		}
	}
}
// ======================== OUTPUT RAW SCAN FUNCTIONS =========================
// Similar to the reason we needed seperate compareMatrix functions,
// we needed multiple outputMatrix functions
// these functions were only to debug and test program, by outputting the raw
// data to the screen of the EV3.
void outputMatrix1(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", 
						Digit1[rowNum][0], Digit1[rowNum][1], Digit1[rowNum][2],
						Digit1[rowNum][3], Digit1[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
void outputMatrix2(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ",
						Digit2[rowNum][0], Digit2[rowNum][1], Digit2[rowNum][2],
						Digit2[rowNum][3], Digit2[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
void outputMatrix3(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ",
						Digit3[rowNum][0], Digit3[rowNum][1], Digit3[rowNum][2],
						Digit3[rowNum][3], Digit3[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
void outputMatrix4(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ",
						Digit4[rowNum][0], Digit4[rowNum][1], Digit4[rowNum][2],
						Digit4[rowNum][3], Digit4[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
void outputMatrix5(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", 
						Digit5[rowNum][0], Digit5[rowNum][1], Digit5[rowNum][2],
						Digit5[rowNum][3], Digit5[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
void outputMatrix6(){
	int lineNum =0;
	for (int rowNum=0;rowNum<ROW_NUM; rowNum++){
		displayTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ",
						Digit6[rowNum][0], Digit6[rowNum][1], Digit6[rowNum][2],
						Digit6[rowNum][3], Digit6[rowNum][4]);
		lineNum++;
	}
	wait1Msec(5000);
}
