#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "TimeObj.h"
#include "timeManager.h"
#include "LEDManager.h"
#include "wifiManager.h"

int previous = -1;

void loop()
{
  TimeObj currentTime = getCurrentTime();

  // Serial.print(F("Time: "));
  // Serial.print(currentTime.hour);
  // Serial.print(F(":"));
  // Serial.println(currentTime.minute);

  if (currentTime.minute != previous)
  {
    LEDManager(currentTime.hour, currentTime.minute);
    if (currentTime.hour == 1 && currentTime.minute == 0) { updateLocalTime(); }
    previous = currentTime.minute;
  }
  delay(10000); // 10s
}

void setup()
{
  Serial.begin(9600);

  wifiSetup();
  delay(200);
  updateLocalTime();
  delay(200);
  ledSetup();
  delay(200);
  spiffsSetup();
  delay(200);
  serverSetup();
  delay(200);
  // Serial.println(F("Setup done"));
}