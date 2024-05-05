#include <WiFi.h>
#include "LEDManager.h"

int hour_pin_tab[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
int minute_pin_tab[] = {12, 12, 12, 12, 12, 12};

void LEDManager(int hour, int minute)
{
  minute = floor(minute / 10);
  hour = hour % 12;

  for (int i = 0; i < 13; i++)
  {
    digitalWrite(hour_pin_tab[i], i == hour);
  }

  for (int i = 0; i < 6; i++)
  {
    digitalWrite(minute_pin_tab[i], i == minute);
  }
}

void setAllLED(bool state)
{
  // Serial.println(" Set all LED " + state); // TODO: Remove this line
  
  for (int i = 0; i < 13; i++)
  {
    digitalWrite(hour_pin_tab[i], state);
  }

  for (int i = 0; i < 6; i++)
  {
    digitalWrite(minute_pin_tab[i], state);
  }
}

void ledSetup(){
  for (int i = 0; i < 13; i++)
  {
    pinMode(hour_pin_tab[i], OUTPUT);
  }

  for (int i = 0; i < 6; i++)
  {
    pinMode(minute_pin_tab[i], OUTPUT);
  }
}