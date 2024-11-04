#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "TimeObj.h"
#include "timeManager.h"
#include "LEDManager.h"
#include "wifiManager.h"

void loop()
{
  delay(1000); // TODO change to 600s

  TimeObj currentTime = getCurrentTime(); // TODO comment all Serial.print

  Serial.print(F("Time: "));
  Serial.print(currentTime.hour);
  Serial.print(F(":"));
  Serial.println(currentTime.minute);

  LEDManager(currentTime.hour, currentTime.minute);
  if (currentTime.hour == 5 && currentTime.minute == 0) {updateLocalTime();}
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
  Serial.println(F("Setup done"));
}