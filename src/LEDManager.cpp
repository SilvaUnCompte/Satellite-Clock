#include <WiFi.h>
#include <Preferences.h>
#include "LEDManager.h"

const int PIN_MIDDAY = 32;
const int PIN_MIDNIGHT = 14;
const int PIN_HOUR = 04;

int pin_used[21] = {00, 01, 02, 03, 04, 05, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33}; // also can use 15
int hour_pin_tab[11] = {33, 26, 13, 02, 01, 05, 25, 27, 12, 17, 16};									 // Commence par "une"
int minute_pin_tab[5][2] = {{03}, {23}, {19}, {21, 18}, {22, 00}};										 // Commence par "dix"

void LEDManager(int hour, int minute)
{
	Preferences preferences;
	preferences.begin("config", true);
	hour += preferences.getInt("utc", 0);
	int on_off = preferences.getInt("on_off", 1);
	preferences.end();

	bool isMidday = (hour == 12);

	minute = floor(minute / 10);
	hour = hour % 12;

	setAllLED(false);
	if (on_off == 0){return;}


	// Set the hour LED
	if (hour != 0)
	{
		digitalWrite(hour_pin_tab[hour - 1], HIGH);
		digitalWrite(PIN_HOUR, HIGH); // 'Heure'
	}
	else
	{
		digitalWrite(isMidday ? PIN_MIDDAY : PIN_MIDNIGHT, HIGH);
	}

	// Set the minute LED
	if (minute != 0)
	{
		digitalWrite(minute_pin_tab[minute - 1][0], HIGH);

		if (minute >= 4) {
			digitalWrite(minute_pin_tab[minute - 1][1], HIGH);
		}
	}
}

void setAllLED(bool state)
{
	// Serial.println(" Set all LED to: " + state);

	for (int i = 0; i < 21; i++)
	{
		digitalWrite(pin_used[i], state);
	}
}

void ledSetup()
{
	for (int i = 0; i < 21; i++)
	{
		pinMode(pin_used[i], OUTPUT);
	}
}