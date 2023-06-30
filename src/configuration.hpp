#pragma once
#include "Constants.hpp"

//#define ESP32

#define SERVER_NAME "TCN"
#define MANUFACTURER "Christian Kardach"
#define MANUFACTURER_VERSION "1.1"
#define LOCATION "SE"

//#define BOARD BOARD_ESP8266_RELAY_MODULE
#define BOARD BOARD_OPENASTROPOWERHUB

#define DEVICE_NAME "TCN Power Switch"
#define DEVICE_TYPE "Switch"
#define DEVICE_NR 0
#define UNIQUE_CLIENT_ID "9be62a4558494b638924267778cd0350" // https://www.guidgenerator.com/online-guid-generator.aspx

#define DESCRIPTION "Mount ASCOM Switch for controlling power supplies"
#define DRIVER_INFO "TCN ASCOM Alpaca Driver"
#define DRIVER_VERSION "1.1"

#define EEPROM_SIZE 512
// Zero based
#if BOARD == BOARD_OPENASTROPOWERHUB
#define NR_OF_RELAYS 5
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
#define NR_OF_RELAYS 16
#endif

#define RELAY_DATA_PIN 14
#define RELAY_LATCH_PIN 12
#define RELAY_CLOCK_PIN 13
#define RELAY_OE_PIN 5
const int RELAY_PINS[] = {8, 7, 6, 5, 0};
