// TODO: write code to show everything but scanning working perfectly - just comment out the scan portion
// TODO: make robot move forward before writing after scanning
/*SOURCES:
For sound: http://help.robotc.net/WebHelpMindstorms/index.htm#Resources/topics/
LEGO_EV3/ROBOTC/Sounds/playSoundFile.htm
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
const int ROW_NUM_TOTAL = 20;
const int COL_NUM_TOTAL = 15;
const int MOTOR_PEN = motorA;
const int MOTOR_AXIAL = motorC;
const int MOTOR_BELT = motorB;
const int COLOR_SENS = S2;
const int SOUND_SENSOR = S1;
const int PEN_SPEED_FORWARD = 5;
const int PEN_SPEED_BACKWARD = -5;

// ============================= INITILIAZE ARRAYS ============================
int matrix[2][3] = {{1, 1, 7},
					{1, 2, 9}}; // the final matrix, used for rref computation

// ============================ FUNCTION PROTOYPES ============================

// ============================ SCANNING FUNCTIONS ===========================
void nextPixelRight();
void nextLineDown();
void goFullyLeft();
void output2By3Matrix();
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
	SensorType[COLOR_SENS] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOR_SENS] = modeEV3Color_Reflected;
	wait1Msec(50);
	SensorType[SOUND_SENSOR] = sensorSoundDB;
	// we used the automatic robotc sensor generator to learn the proper name
	// for the "Legacy NXT Sound sensor"
	wait1Msec(50);

	bool hasYelledEnough = false;
	while(SensorValue[SOUND_SENSOR] < 90){}
	// dont start until someone starts yelling
 	clearTimer(T1);
 	while(SensorValue[SOUND_SENSOR] >70 && !hasYelledEnough){
 		if(time1[T1] > 1000){ // if they have been yelling for 1 second
 			hasYelledEnough = true;
 		}
	}
	hasYelledEnough=true;
	if(hasYelledEnough){
		output2By3Matrix();//outputing the recognized matrix
		wait1Msec(15000);
		eraseDisplay();
		computeMatrix(); // taking the matrix to rref
		eraseDisplay();
		output2By3Matrix(); // outputing the rref version on the screen
		wait1Msec(10000);
		for (int index = 0; index < 2; index++){
			for (int count = 0; count < 3; count++){
				if (matrix[index][count] >= 10){
					int sum = matrix[index][count] - 10;
					matrix[index][count] -= sum+1;
					// this is only in case our scan doesn't have a single digit solution
					// i.e. if it scans improperly
				}
				if (matrix[index][count] < 0){
					matrix[index][count] *= -1 ;
					// output something in case we didn't get a positive solution
					// as we are not able to output negative signs
					// this is only in case our scan doesn't have a positive solution
				}
			}
		}
		writeSolvedMatrix();//outputing the rref of the matrix onto a whiteboard
	}
	else{ // if the user didn't yell for 2 seconds.
		//http://help.robotc.net/WebHelpMindstorms/index.htm#Resources/topics/
		//LEGO_EV3/ROBOTC/Sounds/playSoundFile.htm
		setSoundVolume(100);	//Sets the sound volume of the EV3 speaker to 75
		playSound(soundDownwardTones);
		// Starts playing the built in sound 'soundDownwardTones.rsf' on the EV3
		sleep(3000); // allows time for the robot to play the entire sound file
	}
}
// =========================== END OF TASK MAIN ===============================

// ============================ NEXT PIXEL RIGHT =============================
void nextPixelRight(){
	motor[MOTOR_BELT]=-30;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT] >= (-1)*WIDTH*SWEEP_CONVERSION){}
	motor[MOTOR_BELT]=0;
}

// ============================ NEXT LINE DOWN =============================
void nextLineDown(){
	motor[MOTOR_AXIAL]=-30;
	nMotorEncoder[MOTOR_AXIAL]=0;
	while(nMotorEncoder[MOTOR_AXIAL] >= (-1)*HEIGHT*AXIAL_CONVERSION){}
	motor[MOTOR_AXIAL]=0;
}
// ============================ GO FULLY LEFT =============================
void goFullyLeft(){
	motor[MOTOR_BELT]=50;
	nMotorEncoder[MOTOR_BELT]=0;
	while(nMotorEncoder[MOTOR_BELT] < 16*WIDTH*SWEEP_CONVERSION){}
	motor[MOTOR_BELT]=0;
}
// ============================ OUTPUT MATRIX ===============================
void output2By3Matrix(){
	int lineNum =0;
	for (int i=0;i<2; i++){
		displayBigTextLine(lineNum, "   %d  %d  | %d  ", matrix[i][0],
							matrix[i][1], matrix[i][2]);
		lineNum+=3;
	}
}
// ============================ WRITING FUNCTIONS =============================

// ============================ MOVE ROBOT DOWN ==============================
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
// ============================ MOVE NEXT ROW ================================
void moveNextRow(){
	nMotorEncoder[MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 30;
	// move to the left most column
	while(nMotorEncoder[MOTOR_BELT] <=SWEEP_CONVERSION*15){}

	motor[MOTOR_BELT] = 0;
	// moving then row down one
	moveRobotDown(13,true);
}
// =============================== MOVE RIGHT =================================
void moveRight(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = -10;
	while (nMotorEncoder[MOTOR_BELT]/SWEEP_CONVERSION >= (-1)*dist){}
	motor[MOTOR_BELT] = 0;
}
// =============================== MOVE LEFT =================================
void moveLeft(int dist)
{
	motor[MOTOR_BELT] = 0;
	nMotorEncoder [MOTOR_BELT] = 0;
	motor[MOTOR_BELT] = 10;
	while(nMotorEncoder[MOTOR_BELT] < dist*SWEEP_CONVERSION){}
	motor[MOTOR_BELT] = 0;
}
// =============================== PLACE PEN =================================
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
void writeSolvedMatrix(){
	for (int index = 0; index < 2; index++)
	{
		for (int count = 0; count < 3; count++)
		{
			writeNumber(matrix[index][count]);
			moveRight(5);
		}
		moveNextRow();
	}
}

// ========================== RREF FUNCTIONS ==================================

// =========================== SUBTRACT 2 ROWS ===============================
void subtract2rows(int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are using to fix the rowToFix
	for (int j =0; j<3;j++){ // jth column. is this okay?
		matrix[rowToFix][j] = matrix[rowToFix][j] - multiplier*matrix[rowToUse][j];
	}
}
// ============================== SWAP 2 ROWS ================================
// even more useful function in R3
void swap2Rows(int row1, int row2){
	for (int j =0; j<3;j++){
		int temp = matrix[row1][j];
		matrix[row1][j] = matrix[row2][j];
		matrix[row2][j] = temp;
	}
}
// =========================== REDUCE SINGLE ROW ============================
void reduceSingleRow(int row, int column){
	int multiplier = matrix[row][column];
	for (int j =0; j<3;j++){
		matrix[row][j] = matrix[row][j]/multiplier; // since whole number unique solution
	}
}

// =========================== REDUCE FIRST ENTRIES ==========================
void reduceFirstEntries(){
	// if this is called, it means it is not of the form [1
	//													  0] in the first column
		if (matrix[0][0]>matrix[1][0]){ // if column 1 first row's entry is bigger than second row's entry
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
// =========================== REDUCE SECOND ENTRIES ==========================
void reduceSecondEntries(){
	// if this is called, it means it is not of the form [1
	//													  0] in the second column
	// but we know that it is (1,0)T in the first column. That means we only need to reduce the second row column
	// and get rid of the entry in the first row second column. Therefore,
	if (matrix[1][1]!=1){
		reduceSingleRow(1,1); // reduce second row using 2nd entry in 2nd row
	}
	else{
		subtract2rows(matrix[0][1],0,1);
	}
}
// ============================= COMPUTE MATRIX ==============================
void computeMatrix(){
	while ( (matrix[0][0]!=1||matrix[1][0]!=0||matrix[0][1]!=0||matrix[1][1]!=1)
			// while not in rref
			&& !(matrix[0][0]==0 && matrix[0][1]==0) // while not a zero row in the top row
			&& !(matrix[1][0]==0 && matrix[1][1]==0) ){ // while not a zero row in the bottom row
		if (matrix[0][0]!=1 || matrix[1][0]!=0){
			reduceFirstEntries();
		}
		else{ // at this point, the first column is proper
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
		   then the system is consisttent and has no solution
		*/
		setSoundVolume(100);
		playSoundFile("Uh-oh"); // Starts playing a soundfile, on EV3
		sleep(3000);
		displayBigTextLine(1,"Matrix is");
		displayBigTextLine(3," inconsistent.");
		wait1Msec(2000);
	}// otherwise, there is at least one solution
	output2By3Matrix();
	wait1Msec(4000);
}