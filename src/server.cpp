#include <Arduino.h>
#include <Preferences.h>
#include "wifiManager.h"
#include "timeManager.h"
#include "server.h"

AsyncWebServer server(80);

void spiffsSetup()
{
    if (!SPIFFS.begin())
    {
        Serial.println("SPIFFS error");
        return;
    }

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
        Serial.print("File: ");
        Serial.println(file.name());
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
                if (request->hasParam("password") && request->hasParam("ssid") && request->hasParam("utc"))
                {
                    Serial.println("SSID: " + request->getParam("ssid")->value() + " Password: " + request->getParam("password")->value() + " utc: " + request->getParam("utc")->value());
    
                    Preferences preferences;
                    preferences.begin("config", false);
                    preferences.putString("ssid", request->getParam("ssid")->value());
                    preferences.putString("password", request->getParam("password")->value());
                    preferences.putInt("utc", request->getParam("utc")->value().toInt());
                    preferences.end();
    
                    request->send(200);
    
                    connectToWifi();
                } 
                else {
                    request->send(400, "text/text", "Missing parameters");
                } });

    server.on("/update-time", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                Serial.println("Time update requested");
                String success = updateLocalTime() ? "Time updated" : "Something wrong appended";

                request->send(200, "text/json", 
                "{\"confirm_message\":\"" + success + "\"}"); });

    server.on("/get-config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                Serial.println("Variable requested");

                Preferences preferences;
                preferences.begin("config", true);                

                request->send(200, "text/json", 
                "{\"ssid\":\"" + preferences.getString("ssid", "") + 
                "\",\"password\":\"" + preferences.getString("password", "") + 
                "\",\"utc\":\"" + preferences.getInt("utc", 0) +
                "\"}");

                preferences.end(); });

    server.on("/get-connection-status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                Serial.println("Connection status requested: " + String(WiFi.status()));
                request->send(200, "text/text", String(WiFi.status())); });

    server.begin();
    Serial.println("HTTP server started");
}