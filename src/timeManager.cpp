#include <Arduino.h>
#include <WiFi.h>
#include "TimeObj.h"
#include "time.h"
#include "timeManager.h"
#include "wifiManager.h"
#include "gpsManager.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0;

TimeObj getCurrentTime()
{
  if (getNbSatellites() > 1)
  {
    return getCurrentTimeBySatellite();
  }
  return getCurrentTimeByWifi();
}

TimeObj getCurrentTimeBySatellite()
{
  return getGPSTime();
}

TimeObj getCurrentTimeByWifi()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    // Serial.println("Failed to obtain time");
    return {0, 0};
  }

  return {timeinfo.tm_hour, timeinfo.tm_min};
}

bool updateLocalTime()
{
  if (connectToWifi())
  {
    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    // Serial.println("Time updated.");
    getCurrentTime();

    // disconnect WiFi as it's no longer needed
    delay(1000);
    WiFi.disconnect(true);
    return true;
  }
  else
  {
    // Serial.println("No connection to update time.");
    return false;
  }
}