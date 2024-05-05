#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "timeManager.h"

const char *ssid = "127.0.0.1";
const char *password = "LeYuccaSappellePatrick";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

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

void updateLocalTime(){

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // TODO: Faire sécu si arrive pas à se co du tout !!!!
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Time updated.");
  getCurrentTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
