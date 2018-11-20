// TODO: initialize arrays
#include "PC_FileIO.c"

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

// ============================ FUNCTION PROTOYPES ============================

// ============================ SCANNING FUNCTIONS ===========================
void nextPixelRight();
void nextLineDown();
void goFullyLeft();
void outputMatrix();
// ======================== DIGIT RECOGNITION TESTS ===========================
int compareMatrix1();
int compareMatrix2();
int compareMatrix3();
int compareMatrix4();
int compareMatrix5();
int compareMatrix6();
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
void outputWrite(int value);
void writeSolvedMatrix();
// ============================= RREF FUNCTIONS ==============================
void computeMatrix();
void reduceSecondEntries();
void reduceFirstEntries();
void reduceSingleRow(int row, int coloumn);
void swap2Rows(int row1, int row2);
void subtract2rows(int multiplier, int rowToFix, int rowToUse);

// =============================== TASK MAIN  ================================
task main()
{
	string fileName="Numbers.txt";
	// our text file for the predefined library of scans
	const int AXIAL_CONVERSION = 180/(2.75*PI);
	// conversion factor for the wheels that move the entire robot
	const float SWEEP_CONVERSION = 180/(0.725*PI);
	// conversion factor for the gear on the belt that moves the 
	// colour sensor horizontally. Radius of the gear is 0.725 cm
	const float HEIGHT = 1.0; // Height of 1 cell in the printed matrix
	const float WIDTH = 1.1; // Width of 1 cell in the printed matrix
	const int ROW_NUM=9; // number of rows in 1 section of the printed matrix
	const int COL_NUM=5; // number of columns in 1 section of the printed matrix
	// Note: the printed matrix is split up into 6 different sections
	// one for each digit
	const int MOTOR_PEN = motorA;
	const int MOTOR_AXIAL = motorC;
	const int MOTOR_BELT = motorB;
	const int COLOR_SENS = S2;
	const int SOUND_SENSOR = S1;
	const int PEN_SPEED_FORWARD = 5;
	const int PEN_SPEED_BACKWARD = -5;

	TFileHandle fin;
	bool fileOkay=openReadPC(fin,fileName);

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
	if(hasYelledEnough){ //START SCANNING
		bool isBlack = false;
		for(int row=0; row < 20; row++){
			for(int col=0; col <15; col++){
				// determine black or white
				if(SensorValue[COLOR_SENS] < 10){
					isBlack = true;
				}
				else{
					isBlack = false;
				}
				// store in first digit
				if(col<5 && row<9){
					Digit1[row][col]= isBlack;
				}
				// store in second digit
				else if(col>=5 && col<10 && row<9){
					Digit2[row][col-5]= isBlack;
				}
				// store in third digit
				else if(col>=10 && col<15 && row<9){
					Digit3[row][col-10]= isBlack;
				}
				// store in 4th digit
				else if(col<5 && row>11){
					Digit4[row-12][col]= isBlack;
				}
				// 5th
				else if(col>=5 && col<10 && row>11){
					Digit5[row-12][col-5]= isBlack;
				}
				// 6th
				else  if(col>=10 && col<15 && row>11){
					Digit6[row-12][col-10]= isBlack;
				}
				nextPixelRight(); // move colour sensor right on track to
				// the next cell
				wait1Msec(50);
				// the 14th coloumn doesn't scan unless the line below exists
				if (col == 14){
					if(SensorValue[COLOR_SENS] <10){
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
			// i.e. the number of dissimilarities between them
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
		eraseDisplay();
		computeMatrix();
		eraseDisplay();
		outputMatrix();
		wait1Msec(15000);
		for (int index = 0; index < 2; index++){
			for (int count = 0; count < 3; count++){
				if (matrix[index][count] >= 10){
					int sum = matrix[index][count] - 10;
					matrix[index][count] -= sum+1;
					// this is only in case our scan doesn't have a positive solution
					// i.e. if it scans improperly
				}
				if (matrix[index][count] < 0){
					matrix[index][count] *= -1 ; 
					// output something in case we didn't get a positive solution
					// this is only in case our scan doesn't have a positive solution
				}
			}
		}
		writeSolvedMatrix();
	}
	else{ // if the user didn't yell for 2 seconds.
		setSoundVolume(75);	//Sets the sound volume of the EV3 speaker to 75
		playSound(soundDownwardTones);
		// Starts playing a soundfile, 'soundDownwardTones.rsf' on the EV3
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
// ============================ COMPARE MATRIX 1 =============================
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
// ============================ COMPARE MATRIX 2 =============================
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
// ============================ COMPARE MATRIX 3 =============================
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
// ============================ COMPARE MATRIX 4 =============================
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
// ============================ COMPARE MATRIX 5 =============================
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
// ============================ COMPARE MATRIX 6 =============================
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
// ============================ OUTPUT MATRIX ===============================
void outputMatrix(){
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
	moveRobotDown(8, true);
	moveLeft(3);
	moveRobotDown(8, false);
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
	// move up 8
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
	// move up
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
	// move up
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
// ============================ WRITE SOLVED MATRIX ===========================
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

// ========================== RREF FUNCTIONS ==================================

// ============================= SUBTRACT 2 ROWS =============================
void subtract2rows(int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, 
	// rowToUse is the row we are using to fix the rowToFix
	for (int column = 0; column<3; column++){
		matrix[rowToFix][column] = matrix[rowToFix][column] 
								   - multiplier*matrix[rowToUse][column];
	}
}

// ============================== SWAP 2 ROWS ================================
// This is an even more useful function if we were to do a 3x4 augmented matrix 
void swap2Rows(int row1, int row2){
	for (int j =0; j<3;j++){
		int temp = matrix[row1][j];
		matrix[row1][j] = matrix[row2][j];
		matrix[row2][j] = temp;
	}
}
// ============================ REDUCE SINGLE ROW =============================
void reduceSingleRow(int row, int coloumn){
	int multiplier = matrix[row][coloumn];
	for (int j =0; j<3;j++){
		matrix[row][j] = matrix[row][j]/multiplier; // since whole number unique solution
	}
}
// =========================== REDUCE FIRST ENTRIES ===========================
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

// =========================== REDUCE SECOND ENTRIES ==========================
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
// ============================= COMPUTE MATRIX ==============================
void computeMatrix(){
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
		displayBigTextLine(1,"Matrix is inconsistent");
	}
	outputMatrix();
	wait1Msec(4000);
}