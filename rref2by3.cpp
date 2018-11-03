// Abhi's RREF for 2by3 matricies (augmented), that works for only positive entries
// we can implement negative numbers in rref solver by multiplying row by negative 1
// However, this means having to scan in and detect minus signs in OCR
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>	
#include <iomanip>
// in a 2d array, first [] is rows, second [] is coloumns
using namespace std;
// ==================================== OUTPUT MATRIX ===================
void outputMatrix(int A[2][3]){
	for (int i =0;i<2;i++){
		for (int j =0; j<3;j++){
			cout<<A[i][j]<<" ";
			if (j==1)
				cout<<"| ";
		}
		cout<<endl;
	}
}
// ==================================== SUBTRACT 2 ROWS ===================
void subtract2rows(int Augmented[2][3], int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are using to fix the rowToFix
	for (int j =0; j<3;j++){ // jth coloumn. is this okay?
		Augmented[rowToFix][j] = Augmented[rowToFix][j] - multiplier*Augmented[rowToUse][j];
	}
}
// ==================================== SWAP 2 ROWS ===================
// even more useful function in R3
void swap2Rows(int Augmented[2][3], int row1, int row2){
	for (int j =0; j<3;j++){
		int temp = Augmented[row1][j];
		Augmented[row1][j] = Augmented[row2][j];
		Augmented[row2][j] = temp;
	}
}
// ==================================== REDUCE SINGLE ROW ===================
void reduceSingleRow(int Augmented[2][3], int row, int coloumn){
	int multiplier = Augmented[row][coloumn];
	for (int j =0; j<3;j++){
		Augmented[row][j] = Augmented[row][j]/multiplier; // since whole number unique solution
	}
}
// ==================================== SWAP 2 ROWS ===================
void reduceFirstEntries(int ASystem[2][3]){
	// if this is called, it means it is not of the form [1
	//													  0] in the first coloumn
		if (ASystem[0][0]>ASystem[1][0]){ // if coloumn 1 first row's entry is bigger than second row's entry
			if (ASystem[1][0]==0){ // if second entry is 0
				reduceSingleRow(ASystem,1,0); // need to reduce just the first row, using the 1st entry
			}
			else if (ASystem[0][0]-ASystem[1][0]==1){
				 // difference is only positive 1, therefore,
				cout<<"subtracting 2 rows of difference of 1"<<endl;
				subtract2rows(ASystem,1,0,1);// subtract small (second) row from big (first) row
			}
			else{ // some random stuff
				//row 1 = row 1 -2row2
				cout<<"subtracting 2 random rows"<<endl;
				subtract2rows(ASystem, ASystem[0][0]/ASystem[1][0], 0, 1);
			}
		}
		else if (ASystem[0][0]<ASystem[1][0]){ // if second row's colomun 1 entries are bigger
			swap2Rows(ASystem,0,1); // easy way to deal with it
			cout<<"Swapping"<<endl;
		}
		else{ // if equal
			cout<<"subtracting 2 equal rows 1"<<endl;
			subtract2rows(ASystem,1,1,0);

		}
}
void reduceSecondEntries(int ASystem[2][3]){
	// if this is called, it means it is not of the form [1
	//													  0] in the second coloumn
	// but we know that it is (1,0)T in the first coloumn. That means we only need to reduce the second row coloumn
	// and get rid of the entry in the first row second coloumn. Therefore,
	if (ASystem[1][1]!=1){
		cout<<"reducing second row"<<endl;
		reduceSingleRow(ASystem,1,1); // reduce second row using 2nd entry in 2nd row
	}
	else{
		cout<<"Fixing 1st row"<<endl;
		subtract2rows(ASystem,ASystem[0][1],0,1);
	}
}
// ==================================== MAIN ===================
int main(){

	int A[2][3] = {
					{5,3,1},
					{2,3,2},
					}; // gives 5,0 b/c ints
	// sample excersises below: http://tutorial.math.lamar.edu/Classes/Alg/AugmentedMatrix.aspx
	/* TEST CASES (that wont work), bc negative numbers
	int A[2][3] = {
					{3,-2,14},
					{1,3,1},
	};// gives 4,-1
	int A[2][3] = {
					{-2,1,-3},
					{1,-4,-2},
	}; // 2,1, accurately
	int A[2][3] = {
					{3,-6,-9},
					{-2,-2,12},
	}; // 2,1, accurately
*/
	while (A[0][0]!=1 || A[1][0]!=0 || A[0][1]!=0 || A[1][1]!=1){ // while not in rref
		if (A[0][0]!=1 || A[1][0]!=0){
			cout<<"Called Reduce FIRST Entries"<<endl;
			reduceFirstEntries(A);}
		else{ // at this point, the first coloumn is proper
			cout<<"Called Reduce Second Entries"<<endl;
			reduceSecondEntries(A);
		}
		outputMatrix(A);
	}
	cout<<"The final solution is"<<endl;
	outputMatrix(A);
	
}
