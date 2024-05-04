#ifndef SERVER_H
#define SERVER_H

#include <SPIFFS.h> // Contient FS.h
#include <ESPAsyncWebServer.h>

void spiffsSetup();
void serverSetup();
void closeServer();

#endif