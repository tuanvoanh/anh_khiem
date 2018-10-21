#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <Dns.h>
#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dhcp.h>

#include <WebSocketsClient.h>
#include <SocketIoClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266httpUpdate.h>
#include <SimpleTimer.h>
//state
#define NORMAL          0
#define SEND_STATE      1
#define UPDATE_FIRMWARE 2

//
#define BAUDRATE  115200
#define LED 13
#define LEDSYS 2
#define USE_SERIAL Serial
#define BTN 4 
#define SERVER "cretatech.com"
#define PORT 8999
#define URL "http://cretatech.com:8000/download/creta_G.ino.nodemcu.bin"

#define timeReset 120 //minute
//WebSocketsClient webSocket;

int rP(uint8_t a);
void beginSmart();
int initWifi();
void initPort();
int initSystem(void);
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
void updateFirmware();
