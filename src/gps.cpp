#include "gps.h"

TinyGPSPlus gps;

GPSTime getGPSTime()
{
    if (gps.encode(Serial2.read()))
    {
        Serial.print(F("- GPS Time: "));
        if (gps.time.isValid())
        {
            Serial.print(gps.time.hour());
            Serial.print(F(":"));
            Serial.println(gps.time.minute());

            return {gps.time.hour(), gps.time.minute()};
        }
        else
        {
            Serial.println(F("NO DATA"));
        }
    }
    else
    {
        Serial.println(F("GPS not ready"));
    }

    return {0, 0};
}