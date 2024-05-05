#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "timeManager.h"
#include "wifiManager.h"

const char *ssid = "127.0.0.1";
const char *password = "LeYuccaSappellePatrick";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

TimeObj getCurrentTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return {0, 0};
  }

  return {timeinfo.tm_hour, timeinfo.tm_min};
}

void updateLocalTime()
{
  if (connectToWifi())
  {
    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time updated.");
    getCurrentTime();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
  }
  else
  {
    Serial.println("No connection to update time.");
  }
}
