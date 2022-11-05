
This is based on XTronical's I2S Audio Library that uses the ESP32.
You can find the Library from his website: https://www.xtronical.com/i2sprerelease/
You should also check his YouTube channel for other great projects: https://www.youtube.com/channel/UCOjddcYTYcZBGhpBALhX4Kg
---------------------------------------------

<b>Goal:</b>
My intention for this mirror is to hopefully have others use it as well and build on it.

My main interest in it is it's ability to play miltiple audios while being able to control the playback speed of each audio individually.

XTronical has already released a similar library with the ability to read from SD Cards but does not have the ability to change the playback speed of several WAV files individually.
https://www.xtronical.com/i2s-ep3/

My 1st goal, is to add the SD Card option to this library so that I can play larger files directly from the SD Card. As a 1st attempt, I somewhat succeeded but I faced major latency issues. For this repo, I will try another way to tackle it. Wish me luck!

-----------------------------------------

<b>Progress:</b>

Added ability to read WAV file header from SD card.
Now it is able to construct an XT_Wav_Class object using the filename as argument. e.g: XT_Wav_Class MySound("/sample.wav");
To add more WAV files to be played, simple create more XT_Wav_Class objects.




