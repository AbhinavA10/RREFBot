#include "PC_FileIO.c"

string fileName="Numbers.txt";

bool digit[9][5] = {{0,1,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1}};
int matrix[2][3];
bool libraryMatrix[9][5];
int errorList[10];

// returns number of differences between two matrices
int compareMatrix(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(digit[i][j] != libraryMatrix[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}

task main(){
	TFileHandle fin;
	bool fileOkay=openReadPC(fin,fileName);
	int value = 0;
	// for every number represented in text file
	for(int number=0; number<10; number++){
		// populates an array using text file
		for(int i=0; i<9; i++){
			for(int j=0; j<5; j++){
				readIntPC(fin, value);
				libraryMatrix[i][j] = value;
			}
		}
		// fill a list with number of errors between each matrix
		errorList[number] = compareMatrix();
	}

	int smallestError=45;
	int bestEstimate=0;
	for(int index=0; index<9; index++){
		if(errorList[index] < smallestError){
			smallestError = errorList[index];
			bestEstimate = index;
		}
	}
	displayString(2, "%d", bestEstimate);
	wait1Msec(4000);
}
