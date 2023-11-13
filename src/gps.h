#ifndef GPS_H
#define GPS_H

#include <TinyGPSPlus.h>

typedef struct
{
    int hour;
    int minute;
} GPSTime;

GPSTime getGPSTime();

#endif