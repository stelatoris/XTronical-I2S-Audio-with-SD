#include <Arduino.h>
#include "XT_I2S_Audio.h"
#include "WavData.h"
#include "MusicDefinitions.h"

//    SD Card
#define SD_CS 5 // SD Card chip select

//    I2S
#define I2S_DOUT 22 // i2S Data out oin
#define I2S_BCLK 26 // Bit clock
#define I2S_LRC 25  // Left/Right clock, also known as Frame clock or word select

#define POT_SPEED_WAV1_ANALOG_IN 32 // Pin that will connect to the middle pin of the potentiometer.
#define POT_VOL_WAV1_ANALOG_IN 34   // Pin that will connect to the middle pin of the potentiometer.
#define POT_VOL_WAV2_ANALOG_IN 35   // Pin that will connect to the middle pin of the potentiometer.

XT_I2S_Class I2SAudio(I2S_LRC, I2S_BCLK, I2S_DOUT, I2S_NUM_0);

XT_Wav_Class MySound("/sample1.wav");   // Tested with 2 WAV files at 16000 Hz and have no latency issues. Signed 16bit PCM format in Audacity
XT_Wav_Class MySound2("/sample2.wav");  // When using one or more files at 44,000 Hz, I experienced latency issues.

//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
// Defines

float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void SDCardInit()
{
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)
  if (!SD.begin(SD_CS))
  {
    Serial.println("Error talking to SD card!");
    while (true)
      ; // end program
  }
}

void LoadFiles()
{
  MySound.LoadWavFile();
  MySound2.LoadWavFile();
}

void setup()
{
  Serial.begin(9600); // Used for info/debug

  SDCardInit();
  LoadFiles(); // Load all wave files


  MySound.RepeatForever = true;
  MySound.fname = "sample1.wav";

  MySound2.RepeatForever = true;
  MySound2.fname = "sample2.wav";

  I2SAudio.Play(&MySound);
  I2SAudio.Play(&MySound2);
}

void loop()
{
  I2SAudio.FillBuffer();

  MySound.Speed = floatMap(analogRead(POT_SPEED_WAV1_ANALOG_IN), 0, 4095, 0.5, 3.2);


  MySound.Volume = floatMap(analogRead(POT_VOL_WAV1_ANALOG_IN), 0, 4095, 0, 100);
  MySound2.Volume = floatMap(analogRead(POT_VOL_WAV2_ANALOG_IN), 0, 4095, 0, 100);

}
