#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

typedef struct
{
    int hour;
    int minute;
} TimeObj;

TimeObj getCurrentTime();
TimeObj getCurrentTimeBySatellite();
TimeObj getCurrentTimeByWifi();
bool updateLocalTime();

#endif