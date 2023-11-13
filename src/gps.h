#include <TinyGPSPlus.h>

TinyGPSPlus gps;

typedef struct {
    int hour;
    int minute;
} time;

time getGPSTime();