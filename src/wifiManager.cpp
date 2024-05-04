#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "LEDManager.h"

Preferences preferences;

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 0);
IPAddress subnet(255, 255, 255, 0);

void setWifiAP()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP("ESP32-Satellite-Clock");

    setupServer();
    controlAllLED(true);
}

bool wifiSetup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(preferences.getString("ssid", "wrong-ssid"), preferences.getString("password", "password"));
    WiFi.config(local_IP, gateway, subnet);

    Serial.println("Connecting to WiFi");

    closeServer();
    controlAllLED(false);

    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        count++;
        delay(1000);
        Serial.println("Connecting to WiFi..");
        if (count >= 5)
        {
            Serial.println("Connection failed");
            setWifiAP();
            return false;
        }
    }
    Serial.println("Connected!");
    return true;
}