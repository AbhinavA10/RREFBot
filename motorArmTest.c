const int MOTOR_ARM = motorA;
const int MOTOR_MOVE =motorD;
task main(){
	while (true){
		for (int i=0; i<2;i++){
			nMotorEncoder[MOTOR_ARM]=0;
			motor[MOTOR_ARM]=20;
			while (nMotorEncoder<90);
			motor[MOTOR_ARM]=-20;
			while (nMotorEncoder>0);
			motor[MOTOR_ARM]=0;
		}
		motor[MOTOR_MOVE]=20;
		nMotorEncoder[MOTOR_MOVE]=0;
		while (nMotorEncoder[MOTOR_MOVE]>90);
		motor[MOTOR_MOVE]=0;
	}
}