#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "timeManager.h"
#include "LEDManager.h"
#include "wifiManager.h"

void loop()
{
  delay(1000);
  TimeObj currentTime = getCurrentTime();

  Serial.print(F("Time: "));
  Serial.print(currentTime.hour);
  Serial.print(F(":"));
  Serial.println(currentTime.minute);

  // LEDManager(currentTime.hour, currentTime.minute);
}

void setup()
{
  Serial.begin(115200);

  spiffsSetup();
  ledSetup();
  wifiSetup();

  updateLocalTime();
}