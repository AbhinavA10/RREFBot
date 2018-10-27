#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>	
#include <iomanip>
// in a 2d array, first [] is rows, second [] is coloumns
using namespace std;
// ==================================== SUBTRACT 2 ROWS ===================
void subtract2rows(int Augmented[2][3], int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are using to fix the rowToFix
	for (int j =0; j<3;j++){ // jth coloumn. is this okay?
		A[rowToFix][j] = A[rowToFix][j] - multiplier*A[rowToUse][j];
	}
}
// ==================================== SWAP 2 ROWS ===================
// more useful function in R3
void swap2Rows(int Augmented[2][3], int row1, int row2){
	for (int j =0; j<3;j++){
		int temp = Augmented[row1][j];
		Augmented[row1][j] = Augmented[row2][j];
		Augmented[row2][j] = temp;
	}
}
// ==================================== MAIN ===================
int main(){
	int A[2][3] = {
					{5,3,1},
					{2,3,2},
					};

	while (A[0][0]!=1&&A[0][1]!=0&&A[0][1]!=0&&A[0][1]!=1){ // while not in rref
		



		if (A[0][0]>A[1][0] &&){ // if first row's entry is bigger than second row's entry
			if (A[0][0]-A[1][0]!=1){
			//row 1 = row 1 -2row2

				int multiplier = A[0][0]/A[1][0];
				for (int j =0; j<3;j++){ // jth coloumn. is this okay?
					A[0][j] = A[0][j] - 2*A[1][j];
				}
			}
			else{

			}
		}
		else if (A[0][0]<A[1][0]){ // if second row's entries are bigger
			swap2Rows(A[][],0,1)
		}
		else{ // if equal

		}
	}
	for (int i =0;i<2;i++){
		for (int j =0; j<3;j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<A[0][3]<<endl;
	cout<<A[1][3]<<endl;
	
}