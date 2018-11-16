//Program to test Sound sensor.
// Robot will set motorSpeed according to sound sensor level detected

// Tech Specs: https://shop.lego.com/en-US/Sound-Sensor-9845
//http://www.legoengineering.com/nxt-sensors/

//Simple Tutorial: http://cdn.robotc.net/pdfs/nxt/curriculum/Sensing%20-%20Speed%20Based%20Volume%20for%20LEGO.pdf
task main()
{
	const int SOUND_SENSOR = S1;
	// configure sound sensors
	SensorType[SOUND_SENSOR] = sensorSoundDB;
	// we used the automatic robotc thing to generate name of legacy nxt sensor
	wait1Msec(50);
	wait1Msec(50);

 	clearTimer(T1);
 	while(time1[T1] < 60000) // runs for 60 seconds
 	{
	 	motor[motorA] = SensorValue[SOUND_SENSOR]; // higher = louder
	 	displayBigTextLine(6,"%d",SensorValue[SOUND_SENSOR] );
 	}
 	// make program output to text file to see range of sound sensorEV3_sound
 	// we need to make sure ambient sound doesn't accidentally switch it on
}
