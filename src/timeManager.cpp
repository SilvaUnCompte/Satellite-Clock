#include <WiFi.h>
#include "time.h"
#include "timeManager.h"

// Global var
const char *ssid = "127.0.0.1";
const char *password = "LeYuccaSappellePatrick";

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
  // connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  int try_count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    try_count++;
    if (try_count > 10)
    {
      Serial.println("Failed to connect to WiFi");
      return; // Will retry next day
    }
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}