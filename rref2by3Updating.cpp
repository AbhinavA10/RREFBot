// TO DO - add check for inconsistency, divide by zero???
// inconsistency might be fine, but check divide by 0.


// Abhi's RREF for 2by3 matricies (augmented), that works for only positive entries
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>	
#include <iomanip>
// in a 2d array, first [] is rows, second [] is coloumns
using namespace std;

// in a 2d array, first [] is rows, second [] is coloumns
int matrix[2][3] = {
				{1,1,6},
				{1,2,9}
				};
// will give [3 3]T -- as expected
// ==================================== OUTPUT MATRIX ===================
void outputMatrix(){
	for (int i =0;i<2;i++){
		for (int j =0; j<3;j++){
			cout<<matrix[i][j]<<" ";
			if (j==1)
				cout<<"| ";
		}
		cout<<endl;
	}
}

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
				cout<<"reducing 1st row"<<endl;
				reduceSingleRow(1,0); // need to reduce just the first row, using the 1st entry
			}
			else if (matrix[0][0]-matrix[1][0]==1){
				 // difference is only positive 1, therefore,
				cout<<"subtracting 2 rows of difference of 1"<<endl;
				subtract2rows(1,0,1);// subtract small (second) row from big (first) row
			}
			else{ // some random stuff
				//row 1 = row 1 -2row2
				cout<<"subtracting 2 random rows"<<endl;
				subtract2rows(matrix[0][0]/matrix[1][0], 0, 1);
			}
		}
		else if (matrix[0][0]<matrix[1][0]){ // if second row's colomun 1 entries are bigger
			swap2Rows(0,1); // easy way to deal with it
			cout<<"Swapping"<<endl;
		}
		else{ // if equal
			cout<<"subtracting 2 equal rows"<<endl;
			subtract2rows(1,1,0);

		}
}
void reduceSecondEntries(){
	// if this is called, it means it is not of the form [1
	//													  0] in the second coloumn
	// but we know that it is (1,0)T in the first coloumn. That means we only need to reduce the second row coloumn
	// and get rid of the entry in the first row second coloumn. Therefore,
	if (matrix[1][1]!=1){
		cout<<"reducing second row"<<endl;
		reduceSingleRow(1,1); // reduce second row using 2nd entry in 2nd row
	}
	else{
		cout<<"Fixing 1st row"<<endl;
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
	while (matrix[0][0]!=1 || matrix[1][0]!=0 || matrix[0][1]!=0 || matrix[1][1]!=1){ // while not in rref
		if (matrix[0][0]!=1 || matrix[1][0]!=0){
			cout<<"Called Reduce FIRST Entries"<<endl;
			reduceFirstEntries();}
		else{ // at this point, the first coloumn is proper
			cout<<"Called Reduce Second Entries"<<endl;
			reduceSecondEntries();
		}
		outputMatrix();
	}
	cout<<"The final solution is"<<endl;
	outputMatrix();
}
/* FROM ROBOTC ONE:
// ============================= COMPUTE MATRIX ==============================
void computeMatrix(){
	while ((matrix[0][0]!=1 || matrix[1][0]!=0 || matrix[0][1]!=0 || matrix[1][1]!=1)&& !(( (matrix[0][0] == 0 && matrix[1][0] == 0 ) || (matrix[0][1] == 0 && matrix[1][1] == 0 ) ))){ // while not in rref
		if (matrix[0][0]!=1 || matrix[1][0]!=0 ){
			reduceFirstEntries();}
		else{ // at this point, the first coloumn is proper
			reduceSecondEntries();
		}
		output2By3Matrix();
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
	output2By3Matrix();
	wait1Msec(4000);
}

*/
// ==================================== MAIN ===================
int main(){
	computeMatrix();
}
