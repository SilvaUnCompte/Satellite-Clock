#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "TimeObj.h"

TimeObj getCurrentTime();
TimeObj getCurrentTimeBySatellite();
TimeObj getCurrentTimeByWifi();
bool updateLocalTime();

#endif