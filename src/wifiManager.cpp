#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "LEDManager.h"

void setWifiAP()
{
    // Set Static IP address
    IPAddress local_IP(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 0);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP("ESP32-Satellite-Clock");
    Serial.println("WiFi AP is set up: " + WiFi.softAPIP().toString());
}

bool connectToWifi()
{
    Preferences preferences;
    preferences.begin("wifi", false);
    String ssid = preferences.getString("ssid", "s");
    String password = preferences.getString("password", "p");
    preferences.end();

    // Connect to Wi-Fi
    Serial.println("Connecting to " + ssid);
    WiFi.begin(ssid, password);

    for (int i = 0; i < 10; i++)
    {
        delay(500);
        Serial.print('.');
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
    WiFi.mode(WIFI_AP_STA);
    setWifiAP();
}