task main()
{
	const int SOUND_SENSOR = S1;
	// configure sound sensors
	SensorType[SOUND_SENSOR] = sensorSoundDB;
	// we used the automatic robotc thing to generate name of legacy nxt sensor
	wait1Msec(50);
	bool begin = false;
	// dont start until someone starts yelling
	while(SensorValue[SOUND_SENSOR]<80){}
 	clearTimer(T1);
 	while(SensorValue[SOUND_SENSOR] >80&&!begin){
 		// if they have been yelling for 3 seconds
 		if(time1[T1]>2000){
 		 begin = true;
 		}
	}

	if(begin){
		//write REST OF MAIN HERE =========
	
	}
	else{
		//Sets the sound volume of the EV3 speaker to 75
	setSoundVolume(75);
	// Starts playing a soundfile, 'Bravo.rsf' on the EV3
	playSound(soundDownwardTones);
	sleep(3000);
	}


}