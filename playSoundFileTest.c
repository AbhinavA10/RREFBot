//Program to test playing a sound file on EV3
// need to convert to wav, then to rso or rsf?
	//http://www.robotc.net/forums/viewtopic.php?f=19&t=492
//converting file using graphical scratch-type software https://builderdude35.com/2016/01/07/how-to-make-custom-sound-files-in-ev3-g/
//https://www.ev3dev.org/docs/tutorials/using-ev3-speaker/
void checkSoundFile(const char *pFileName)
{
   bool bExists = bEv3FileExists(pFileName);
   while (!bSoundQueueAvailable){}
   playSoundFile(pFileName);
}
task main()
{
   setSoundVolume(30);
   checkSoundFile("/home/root/lms2012/prjs/rc/No_Beacon");      // Custom soundfile: No_Beacon.rsf
   sleep(1000);
}