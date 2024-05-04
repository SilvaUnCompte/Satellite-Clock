#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "timeManager.h"
#include "LEDManager.h"
#include "wifiManager.h"

void loop()
{
  delay(1000); // TODO change to 10s
  TimeObj currentTime = getCurrentTime();

  Serial.print(F("Time: "));
  Serial.print(currentTime.hour);
  Serial.print(F(":"));
  Serial.println(currentTime.minute);

  // updateLocalTime(); 

  // LEDManager(currentTime.hour, currentTime.minute);
}

void setup()
{
  Serial.begin(9600);

  ledSetup();
  delay(50);
  wifiSetup();
  delay(50);
  spiffsSetup();
  delay(50);
  serverSetup();

  updateLocalTime();
}