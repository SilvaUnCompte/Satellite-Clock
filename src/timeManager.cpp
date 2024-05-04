#include <WiFi.h>
#include <time.h>
#include "timeManager.h"
#include "wifiManager.h"
#include "LEDManager.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

TimeObj getCurrentTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return {0, 0};
  }

  return {timeinfo.tm_hour, timeinfo.tm_min};
}

void updateLocalTime()
{
  // check if wifi is connected
  if(WiFi.status() != WL_CONNECTED)
  {
    setAllLED(true);
    return;
  }

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getCurrentTime();
  Serial.println("Time updated.");

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
}