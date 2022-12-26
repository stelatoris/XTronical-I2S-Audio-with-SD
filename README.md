
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

- Added ability to read WAV file header from SD card.
  Now it is able to construct an XT_Wav_Class object using the filename as argument. e.g: XT_Wav_Class MySound("/sample.wav");
  To add more WAV files to be played, simple create more XT_Wav_Class objects.

- Can Play one WAV file from SD card, either Stereo or Mono Channels. 18-12-2022

<b>Small success!</b>
26-12-2022
- It can now Play two WAV files from SD card with no latency issues when using WAV files that have a sample rate of 16,000 Hz.
I tied two files with 44,100 Hz and have experienced latency issues.
The latency issue is expressed by the program not able to exit the `while (NumBytesWritten > 0)` loop in the void XT_I2S_Class::FillBuffer(). It appears that the 
i2s_write(I2S_NUM_0, &MixedSample, 4, &NumBytesWritten, 1); function keeps returning `NumBytesWritten` greater than 0. At this point, it never exits to the main prog loop().




