// #include <WiFi.h>
// #include <time.h>
// #include "wifiManager.h"
// #include "LEDManager.h"

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

// void updateLocalTime()
// {  
//   if (WiFi.status() != WL_CONNECTED)
//   {
//     setAllLED(true);
//     return;
//   }

//   // init and get the time
//   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//   Serial.println("Time updated.");
//   getCurrentTime();
// }



// void printLocalTime(){
//   struct tm timeinfo;
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("Failed to obtain time");
//     return;
//   }
//   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//   Serial.print("Day of week: ");
//   Serial.println(&timeinfo, "%A");
//   Serial.print("Month: ");
//   Serial.println(&timeinfo, "%B");
//   Serial.print("Day of Month: ");
//   Serial.println(&timeinfo, "%d");
//   Serial.print("Year: ");
//   Serial.println(&timeinfo, "%Y");
//   Serial.print("Hour: ");
//   Serial.println(&timeinfo, "%H");
//   Serial.print("Hour (12 hour format): ");
//   Serial.println(&timeinfo, "%I");
//   Serial.print("Minute: ");
//   Serial.println(&timeinfo, "%M");
//   Serial.print("Second: ");
//   Serial.println(&timeinfo, "%S");

//   Serial.println("Time variables");
//   char timeHour[3];
//   strftime(timeHour,3, "%H", &timeinfo);
//   Serial.println(timeHour);
//   char timeWeekDay[10];
//   strftime(timeWeekDay,10, "%A", &timeinfo);
//   Serial.println(timeWeekDay);
//   Serial.println();
// }

void updateLocalTime(){

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  TimeObj test = getCurrentTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
