//http://help.robotc.net/WebHelpMindstorms/index.htm#Resources/topics/LEGO_EV3/ROBOTC/Sounds/playSoundFile.htm
task main()
{
	//Sets the sound volume of the EV3 speaker to 75
	setSoundVolume(75);
	// Starts playing a soundfile, 'Bravo.rsf' on the EV3
	playSoundFile("Okey-dokey"); //  for preinstalled sound files?
	// Gives the file 2 seconds to play
	sleep(2000);
	playSound(soundDownwardTones);
	sleep(3000);
}