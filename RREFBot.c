// A useful link maybe: http://cdn.robotc.net/pdfs/nxt/reference/hp_res_words.pdf
const WHEEL_RADIUS = 2.75
const int MOTOR_ARM = motorA;
const int MOTOR_MOVE =motorD;

float getEncCountFromWheelDist(float distance){
	return distance * (180.0/(WHEEL_RADIUS*PI));
}
float getWheelDistFromEncCount(double count){
	return count / (180.0/(WHEEL_RADIUS*PI));
}
void outputMatrix(){
	int lineNum = 0;
	for (int i=0;i<8; i++){
		displayBigTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", A[i][0], A[i][1], A[i][2], A[i][3] A[i][4]);
		lineNum+=3;
	}
}
void matchData();


int A[2][3] = {{0,0,0},{0,0,0}};
task main(){
	
}