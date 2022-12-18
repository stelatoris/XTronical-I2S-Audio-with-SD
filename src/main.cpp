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


XT_I2S_Class I2SAudio(I2S_LRC, I2S_BCLK, I2S_DOUT, I2S_NUM_0);

XT_Wav_Class MySound("/alert1.wav");

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
}

void setup()
{
  Serial.begin(9600); // Used for info/debug
  
  SDCardInit();
  LoadFiles();  // Load all wave files

  MySound.RepeatForever = true;
  MySound.Volume = 100;

  I2SAudio.Play(&MySound);
}

void loop()
{
  I2SAudio.FillBuffer();
  //MySound.Speed = floatMap(analogRead(POT_SPEED_WAV1_ANALOG_IN), 0, 4095, 0.0, 4.0);
  Serial.println("-------------------------------------");

  //MySound.Volume = floatMap(analogRead(POT_VOL_WAV1_ANALOG_IN), 0, 4095, 0, 150);
}