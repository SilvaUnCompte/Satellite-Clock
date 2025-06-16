#include <WiFi.h>
#include <Preferences.h>
#include "LEDManager.h"

const int PIN_MIDDAY = 32;
const int PIN_MIDNIGHT = 14;
const int PIN_HOUR = 04;

int pin_used[21] = {00, 01, 02, 03, 04, 05, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33}; // also can use 15
int hour_pin_tab[11] = {33, 26, 13, 02, 01, 05, 25, 27, 12, 17, 16};									 // Commence par "une"
int minute_pin_tab[5][2] = {{03}, {23}, {19}, {21, 18}, {22, 00}};										 // Commence par "dix"

bool getLEDStatus(int on_off, float on_start, float on_end, int hour, int minute)
{
	float time = hour + (minute / 60.0);

	if (on_off == 0)
	{
		return false; // LED is off
	}

	if (on_start < on_end)
	{
		return (time >= on_start && time <= on_end);
	}
	else
	{
		return (time >= on_start || time <= on_end); // If start == end, always on
	}
}

void LEDManager(int hour, int minute)
{
	Preferences preferences;
	preferences.begin("config", true);
	int on_off = preferences.getInt("on_off", 1);
	float on_start = preferences.getFloat("on_start", 0.0);
	float on_end = preferences.getFloat("on_end", 24.0);
	hour += preferences.getInt("utc", 0);
	preferences.end();

	// Off system
	setAllLED(false);
	if (getLEDStatus(on_off, on_start, on_end, hour, minute) == false)
	{
		return; // If LED is off, do not proceed
	}

	// Set the hour and minute to the correct values
	bool isMidday = (hour == 12);
	minute = floor(minute / 10);
	hour = hour % 12;

	// Set the hour LED
	if (hour != 0)
	{
		digitalWrite(hour_pin_tab[hour - 1], HIGH);
		digitalWrite(PIN_HOUR, HIGH); // show word 'Heure'
	}
	else
	{
		digitalWrite(isMidday ? PIN_MIDDAY : PIN_MIDNIGHT, HIGH);
	}

	// Set the minute LED
	if (minute != 0)
	{
		digitalWrite(minute_pin_tab[minute - 1][0], HIGH);

		if (minute >= 4)
		{
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