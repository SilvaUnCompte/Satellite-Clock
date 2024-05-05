#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "LEDManager.h"

// Set Static IP address
IPAddress gateway(192, 168, 0, 0);
IPAddress subnet(255, 255, 255, 0);

void setWifiAP()
{
    IPAddress local_IP(192, 168, 0, 1);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP("ESP32-Satellite-Clock");
    Serial.println("WiFi AP is set up");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}

bool connectToWifi()
{
    Preferences preferences;
    preferences.begin("wifi", false);
    WiFi.begin(preferences.getString("ssid", "s"), preferences.getString("password", "p"));
    preferences.end();

    IPAddress local_IP(192, 168, 0, 12);
    WiFi.config(local_IP, gateway, subnet);
    Serial.print("Connecting to WiFi.");

    for (int i = 0; i < 5; i++)
    {
        delay(1000);
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

bool wifiSetup()
{
    // WiFi.mode(WIFI_AP_STA);
    // setWifiAP();
    // return connectToWifi();

    WiFi.mode(WIFI_STA);
    return connectToWifi();
}