#include "PC_FileIO.c"

string fileName="Numbers.txt";

bool digit[9][5];
int matrix[2][3];
bool libraryMatrix[9][5];
int errorList[10];

// returns number of differences between two matrices
int compareMatrix(){
	int errorCount=0;
	for(int i=0; i<9; i++){
		for(int j=0; j<5; j++){
			if(scan[i][j] != control[i][j]){
				errorCount++;
			}
		}
	}
	return errorCount;
}

task main(){
	TFileHandle fin;
	bool fileOkay=openReadPC(fin,"fileRead.txt");

	// for every number represented in text file
	for(int number=0; number<10){
		// populates an array using text file 
		for(int i=0; i<9; i++){
			for(int j=0; j<5; j++){
				readIntPC(fin, value);
				libraryMatrix[i][j] = value;
			}
		}
		// fill a list with number of errors between each matrix
		errorList[number] = compareMatrix(digit[9][5], matrix[9][5]);
	}
	
	int smallestError=45;
	int bestEstimate=0;
	for(int index=0; index<9; index++){
		if(errorList[index] < smallestError){
			smallesError = errorList[index];
			bestEstimate = index;
		}
	}
	

	//display string bestEstimate
	

}


/*
int estimateDigit(bool matrix[9][5]){
	// for every number represented in text file
	for(int number=0; number<10){
		// populates an array using text file 
		for(int i=0; i<9; i++){
			for(int j=0; j<5; j++){
				readIntPC(fin, value);
				libraryMatrix[i][j] = value;
			}
		}
		// fill a list with number of errors between each matrix
		errorList[number] = compareMatrix(digit[9][5], matrix[9][5]);
	}
	
	int smallestError=45;
	int bestEstimate=0;
	for(int index=0; index<9; index++){
		if(errorList[index] < smallestError){
			smallesError = errorList[index];
			bestEstimate = index;
		}
	}
	return bestEstimate;
}
*/
