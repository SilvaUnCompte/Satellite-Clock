#include <Arduino.h>
#include <Preferences.h>
#include "wifiManager.h"
#include "timeManager.h"
#include "LEDManager.h"
#include "gpsManager.h"
#include "server.h"

AsyncWebServer server(80);

void spiffsSetup()
{
    if (!SPIFFS.begin())
    {
        // Serial.println("SPIFFS error");
        return;
    }

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
        // Serial.print("File: ");
        // Serial.println(file.name());
        file.close();
        file = root.openNextFile();
    }
}

void serverSetup()
{
    // ------------------ File System ------------------

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/javascript"); });

    // ------------------ Page Back ------------------

    server.on("/update-config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if (request->hasParam("password") && request->hasParam("ssid") && request->hasParam("utc") && request->hasParam("on_off") && request->hasParam("on_start") && request->hasParam("on_end"))
                {
                    // Serial.println("SSID: " + request->getParam("ssid")->value() + " Password: " + request->getParam("password")->value() + " utc: " + request->getParam("utc")->value() + " on_off: " + request->getParam("on_off")->value() + " on_start: " + request->getParam("on_start")->value() + " on_end: " + request->getParam("on_end")->value());
    
                    Preferences preferences;
                    preferences.begin("config", false);
                    preferences.putString("ssid", request->getParam("ssid")->value());
                    preferences.putString("password", request->getParam("password")->value());
                    preferences.putInt("utc", request->getParam("utc")->value().toInt());
                    preferences.putInt("on_off", request->getParam("on_off")->value().toInt());
                    preferences.putFloat("on_start", request->getParam("on_start")->value().toFloat());
                    preferences.putFloat("on_end", request->getParam("on_end")->value().toFloat());
                    preferences.end();
    
                    request->send(200);
                    
                    if (connectToWifi()){
                        TimeObj currentTime = getCurrentTime();
                        LEDManager(currentTime.hour, currentTime.minute);
                    }
                } 
                else {
                    request->send(400, "text/text", "Missing parameters");
                } });

    server.on("/update-time", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                // Serial.println("Time update requested");
                String confirm_message;

                if (updateLocalTime()){
                    confirm_message = "Time updated";
                    TimeObj currentTime = getCurrentTime();
                    LEDManager(currentTime.hour, currentTime.minute);
                }
                else{
                    confirm_message = "Something wrong appended";
                }

                request->send(200, "text/json", 
                "{\"confirm_message\":\"" + confirm_message + "\"}"); });

    server.on("/get-config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                // Serial.println("Variable requested");

                Preferences preferences;
                preferences.begin("config", true);                

                request->send(200, "text/json", 
                "{\"ssid\":\"" + preferences.getString("ssid", "") + 
                "\",\"password\":\"" + preferences.getString("password", "") + 
                "\",\"utc\":\"" + preferences.getInt("utc", 0) +
                "\",\"on_off\":\"" + preferences.getInt("on_off", 1) +
                "\",\"on_start\":\"" + preferences.getFloat("on_start", 0.0) +
                "\",\"on_end\":\"" + preferences.getFloat("on_end", 24.0) +
                "\"}");

                preferences.end(); });

    server.on("/get-connection-status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                // Serial.println("Connection status requested: " + String(WiFi.status()));
                request->send(200, "text/text", String(WiFi.status())); });

    server.on("/get-satellite-count", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/text", String(getNbSatellites())); });

    server.begin();
    // Serial.println("HTTP server started");
}