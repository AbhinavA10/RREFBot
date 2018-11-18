// A useful link maybe: http://cdn.robotc.net/pdfs/nxt/reference/hp_res_words.pdf
const int WHEEL_RADIUS = 2.75;
const int MOTOR_ARM = motorD;
const int MOTOR_MOVE =motorA;

float getEncCountFromWheelDist(float distance){
	return distance * (180.0/(WHEEL_RADIUS*PI));
}
float getWheelDistFromEncCount(double count){
	return count / (180.0/(WHEEL_RADIUS*PI));
}

int A[2][3] = {
					{0,0,0},
					{0,0,0}};
void outputMatrix(){
	int lineNum = 0;
	for (int i=0;i<8; i++){
		displayBigTextLine(lineNum, "   %d  %d  %d  %d  %d  %d  ", A[i][0], A[i][1], A[i][2]);
		lineNum+=3;
	}
}
task main(){
motor[MOTOR_MOVE]=30;
wait1Msec(1000);
motor[MOTOR_MOVE]=-30;
wait1Msec(1000);
}
