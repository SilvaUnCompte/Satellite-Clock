#include <Arduino.h>
#include "gps.h"

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600);

  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
}

void loop()
{
  if (Serial2.available() > 0)
  {
    time t = getGPSTime();
    Serial.print(t.hour + ":" + t.minute);
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS data received: check wiring"));
  }
}