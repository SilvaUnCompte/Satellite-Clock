#include <Arduino.h>
#include "gps.h"

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600);

  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
}

void LEDManager(int hour, int minute)
{
  int hour_pin_tab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int minute_pin_tab[] = {0, 1, 2, 3, 4, 5};
  minute = floor(minute / 10);

  for (int i = 0; i < 13; i++)
  {
    digitalWrite(hour_pin_tab[i], hour_pin_tab[i] == hour);
  }

  for (int i = 0; i < 6; i++)
  {
    digitalWrite(minute_pin_tab[i], minute_pin_tab[i] == minute);
  }
}

void loop()
{
  GPSTime time = getGPSTime();

  Serial.print(F("Time: "));
  Serial.print(time.hour);
  Serial.print(F(":"));
  Serial.println(time.minute);

  delay(1000);

  LEDManager(time.hour, time.minute);
}