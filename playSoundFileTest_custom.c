//Program to test playing a sound file on EV3
// need to convert to wav, then to rs0, then rename as rsf
// then download file to robot
//http://www.robotc.net/forums/viewtopic.php?f=1&t=9711
//converting file using graphical scratch-type software https://builderdude35.com/2016/01/07/how-to-make-custom-sound-files-in-ev3-g/
//https://www.ev3dev.org/docs/tutorials/using-ev3-speaker/
//https://stackoverflow.com/questions/32710483/robotc-upload-sound-file-to-ev3
void checkSoundFile(){
	bool bExists = bEv3FileExists("/home/root/lms2012/prjs/rc-data/customTest2.rsf");
	if(bExists)
		drawBmpfile(0, 127, "Thumbs up");
	else
		drawBmpfile(0, 127, "Thumbs down");
	while (!bSoundQueueAvailable){}
	playSoundFile("/home/root/lms2012/prjs/rc-data/customTest2.rsf");
}
task main()
{
   setSoundVolume(100);
   checkSoundFile();
   sleep(2000);
}
