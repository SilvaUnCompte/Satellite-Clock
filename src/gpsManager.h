#ifndef GPS_H
#define GPS_H

#include <TinyGPSPlus.h>

#include "TimeObj.h"

TimeObj getGPSTime();
int getNbSatellites();

#endif