// Abhi's RREF for 2by3 matricies (augmented), that works for only positive entries

// in a 2d array, first [] is rows, second [] is coloumns
int Augmented[2][3] = {
				{1,1,5},
				{2,1,7}
				};
// Should give [2 3]T -- and it does
// ==================================== OUTPUT MATRIX ===================
void outputMatrix(){
	int lineNum =0;
	for (int i=0;i<2; i++){
		displayBigTextLine(lineNum, "   %d  %d  | %d  ", Augmented[i][0], Augmented[i][1], Augmented[i][2]);
		lineNum+=3;
	}
}
// ==================================== SUBTRACT 2 ROWS ===================
void subtract2rows(int multiplier, int rowToFix, int rowToUse){
	// rowToFix is the row we are doing the ERO on, rowToUse is the row we are using to fix the rowToFix
	for (int j =0; j<3;j++){ // jth coloumn. is this okay?
		Augmented[rowToFix][j] = Augmented[rowToFix][j] - multiplier*Augmented[rowToUse][j];
	}
}
// ==================================== SWAP 2 ROWS ===================
// even more useful function in R3
void swap2Rows(int row1, int row2){
	for (int j =0; j<3;j++){
		int temp = Augmented[row1][j];
		Augmented[row1][j] = Augmented[row2][j];
		Augmented[row2][j] = temp;
	}
}
// ==================================== REDUCE SINGLE ROW ===================
void reduceSingleRow(int row, int coloumn){
	int multiplier = Augmented[row][coloumn];
	for (int j =0; j<3;j++){
		Augmented[row][j] = Augmented[row][j]/multiplier; // since whole number unique solution
	}
}
// ==================================== SWAP 2 ROWS ===================
void reduceFirstEntries(){
	// if this is called, it means it is not of the form [1
	//													  0] in the first coloumn
		if (Augmented[0][0]>Augmented[1][0]){ // if coloumn 1 first row's entry is bigger than second row's entry
			if (Augmented[1][0]==0){ // if second entry is 0
				reduceSingleRow(1,0); // need to reduce just the first row, using the 1st entry
			}
			else if (Augmented[0][0]-Augmented[1][0]==1){
				 // difference is only positive 1, therefore,
				subtract2rows(1,0,1);// subtract small (second) row from big (first) row
			}
			else{ // some random stuff
				//row 1 = row 1 -2row2
				subtract2rows(Augmented[0][0]/Augmented[1][0], 0, 1);
			}
		}
		else if (Augmented[0][0]<Augmented[1][0]){ // if second row's colomun 1 entries are bigger
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
	if (Augmented[1][1]!=1){
		reduceSingleRow(1,1); // reduce second row using 2nd entry in 2nd row
	}
	else{
		subtract2rows(Augmented[0][1],0,1);
	}
}
// ==================================== MAIN ===================
task main(){
	while (Augmented[0][0]!=1 || Augmented[1][0]!=0 || Augmented[0][1]!=0 || Augmented[1][1]!=1){ // while not in rref
		if (Augmented[0][0]!=1 || Augmented[1][0]!=0){
			reduceFirstEntries();}
		else{ // at this point, the first coloumn is proper
			reduceSecondEntries();
		}
		outputMatrix();
		wait1Msec(500);
	}
	outputMatrix();
	wait1Msec(4000);
}
