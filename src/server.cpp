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

    server.on("/update-credentials", HTTP_GET, [](AsyncWebServerRequest *request)
              {
              if (request->hasParam("password") && request->hasParam("ssid"))
              {
                  // TODO: delete this line
                  Serial.println("SSID: " + request->getParam("ssid")->value() + " Password: " + request->getParam("password")->value());
  
                  Preferences preferences;
                  preferences.begin("wifi", false);
                  preferences.putString("ssid", request->getParam("ssid")->value());
                  preferences.putString("password", request->getParam("password")->value());
                  preferences.end();
  
                  request->send(200);
  
                //   connectToWifi(); /TODO: Décider de comment update le temps avec l'interface
              }
              else
              {
                  request->send(400, "text/plain", "Missing parameters");
              } });

    server.on("/get-credentials", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                Serial.println("Credentials requested");

                Preferences preferences;
                preferences.begin("wifi", true);                

                request->send(200, "text/json", 
                "{\"ssid\":\"" + preferences.getString("ssid", "") + 
                "\",\"password\":\"" + preferences.getString("password", "") + 
                "\"}");

                preferences.end(); });

    server.on("/get-connection-status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                Serial.println("Connection status requested: " + String(WiFi.status()));
                request->send(200, "text/text", String(WiFi.status())); });

    server.begin();
    Serial.println("HTTP server started");
}