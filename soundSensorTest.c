//Program to test Sound sensor.
// Robot will set motorSpeed according to sound sensor level detected

// Tech Specs: https://shop.lego.com/en-US/Sound-Sensor-9845
//http://www.legoengineering.com/nxt-sensors/

//Simple Tutorial: http://cdn.robotc.net/pdfs/nxt/curriculum/Sensing%20-%20Speed%20Based%20Volume%20for%20LEGO.pdf
task main()
{
	const int SOUND_SENSOR = S1;
	// configure sound sensors
	SensorType[SOUND_SENSOR] = sensorEV3_Sound;
	wait1Msec(50);
	SensorMode[SOUND_SENSOR] = modeEV3Sound_SoundDB; // may not work
	wait1Msec(50);
 	
 	ClearTimer(T1);
 	while(time1[T1] < 10000) // runs for 10 seconds
 	{
	 	motor[motorA] = SensorValue[SOUND_SENSOR]; // higher = louder
	 	motor[motorD] = SensorValue[SOUND_SENSOR];
 	}
 	// make program output to text file to see range of sound sensorEV3_sound
 	// we need to make sure ambient sound doesn't accidentally switch it on
}