#include <Arduino.h>
#include "server.h"
#include <Preferences.h>
#include "wifiManager.h"

Preferences preferences;
AsyncWebServer server(80);

void spiffsSetup()
{
    if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS err");
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

void setupServer()
{
    // ------------------ File System ------------------

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/javascript"); });

    // ------------------ Page Stream ------------------

    server.on("/set-wifi", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                if (request->hasParam("password") && request->hasParam("ssid"))
                {
                    // TODO: delete this line
                    Serial.println("SSID: " + request->getParam("ssid")->value() + " Password: " + request->getParam("password")->value());

                    preferences.begin("wifi", false);
                    preferences.putString("ssid", request->getParam("ssid")->value());
                    preferences.putString("password", request->getParam("password")->value());
                    preferences.end();

                    request->send(200);

                    wifiSetup();
                }
                else
                {
                    request->send(400, "text/plain", "Missing parameters");
                } });

    server.begin();
    Serial.println("HTTP server started");
}

void closeServer()
{
    server.end();
    Serial.println("HTTP server closed");
}