#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "LEDManager.h"


bool connectToWifi()
{
    Preferences preferences;
    preferences.begin("wifi", false);
    WiFi.begin(preferences.getString("ssid", "nothing"), preferences.getString("ssid", "wrong"));
    preferences.end();

    for (int i = 0; i < 12; i++)
    {
        delay(500);
        Serial.print('.' + String(WiFi.status()));

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println(" Connected!");
            return true;
        }
    }
    Serial.println(" Connection failed.");
    return false;
}

void wifiSetup()
{
    // Set Static IP address
    IPAddress local_IP(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 0);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP("ESP32-Satellite-Clock");
    
    Serial.println("WiFi AP is set up: " + WiFi.softAPIP().toString());
}