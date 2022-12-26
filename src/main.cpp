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

#define LED_READ_PIN 15 // for debugging
#define LED_DONE_PIN 14  // for debugging

int engine_swtch = 4;
int alert_swtch = 16;
XT_I2S_Class I2SAudio(I2S_LRC, I2S_BCLK, I2S_DOUT, I2S_NUM_0);

XT_Wav_Class MySound("/engine1.wav");
XT_Wav_Class MySound2("/alert1.wav");

String fname{"hello"};

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

  pinMode(engine_swtch, INPUT);
  pinMode(alert_swtch, INPUT);
  pinMode(LED_READ_PIN, OUTPUT);
  pinMode(LED_DONE_PIN, OUTPUT);

  MySound.RepeatForever = false;
  MySound.fname = "engine1.wav";

  MySound2.RepeatForever = false;
  MySound2.fname = "alert1.wav";

  // I2SAudio.Play(&MySound);
  // I2SAudio.Play(&MySound2);
}

void loop()
{
  I2SAudio.FillBuffer();

  MySound.Speed = floatMap(analogRead(POT_SPEED_WAV1_ANALOG_IN), 0, 4095, 0.5, 3.2);
  // Serial.println("-------------------------------------");

  MySound.Volume = floatMap(analogRead(POT_VOL_WAV1_ANALOG_IN), 0, 4095, 0, 100);
  MySound2.Volume = floatMap(analogRead(POT_VOL_WAV2_ANALOG_IN), 0, 4095, 0, 100);

  // engine sound
  if (digitalRead(engine_swtch) == HIGH)
  {
    // Serial.println("Eng ON");
    if (I2SAudio.AlreadyPlaying(&MySound))
    {
      //Serial.println("Eng PLAYING");
    } // do nothing

    else
    {
      Serial.println("Eng ON");
      I2SAudio.Play(&MySound);
    }
  }
  else
  {
    if (I2SAudio.AlreadyPlaying(&MySound))
    { 
      I2SAudio.RemoveFromPlayList(&MySound);
      Serial.println("Eng Removed");
    }
    else {} // do nothing
  }

  // // alert sound -------------------------------------------
  if (digitalRead(alert_swtch) == HIGH)
  {
    // Serial.println("Alert ON");
    if (I2SAudio.AlreadyPlaying(&MySound2))
    {
      //Serial.println("Alert PLAYING");
    } // do nothing

    else
    {
      Serial.println("Alert ON");
      I2SAudio.Play(&MySound2);
    }
  }
  else
  {
    if (I2SAudio.AlreadyPlaying(&MySound2))
    { 
      I2SAudio.RemoveFromPlayList(&MySound2);
      Serial.println("Alert Removed");
    }
    else {} // do nothing
  }
}
