#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

typedef struct
{
    int hour;
    int minute;
} TimeObj;

TimeObj getCurrentTime();
bool updateLocalTime();

#endif