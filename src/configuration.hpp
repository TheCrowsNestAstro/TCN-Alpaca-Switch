#pragma once
#include "Constants.hpp"

#define MQTT_ENABLED FALSE

#define SERVER_NAME "TCN"
#define MANUFACTURER "Christian Kardach"
#define MANUFACTURER_VERSION "1.1"
#define LOCATION "SE"

//#define BOARD BOARD_ESP8266_RELAY_MODULE
#define BOARD BOARD_OPENASTROPOWERHUB

#if BOARD == BOARD_OPENASTROPOWERHUB
#define DEVICE_NAME "TCN Power Switch"
#define DRIVER_INFO "OAPH Alpaca Driver"
#define UNIQUE_CLIENT_ID "785d8e0c4af346208dcd9186a381d8d6" // https://www.guidgenerator.com/online-guid-generator.aspx
#define NR_OF_CHANNELS 5
const int channelMinDefault[] = {0, 0, 0, 0, 0};
const int channelMaxDefault[] = {100, 100, 1, 1, 1};
const int channelStepDefault[] = {1, 1, 1, 1, 1};
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
#define DEVICE_NAME "TCN Power Switch"
#define DRIVER_INFO "TCN ASCOM Alpaca Driver"
#define UNIQUE_CLIENT_ID "9be62a4558494b638924267778cd0350" // https://www.guidgenerator.com/online-guid-generator.aspx
#define NR_OF_CHANNELS 16
const int channelMinDefault[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int channelMaxDefault[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const int channelStepDefault[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
#endif
#define DESCRIPTION "Mount ASCOM Switch for controlling power supplies and dew heaters"
#define DRIVER_VERSION "1.1"

#define DEVICE_TYPE "Switch"
#define DEVICE_NR 0


#define EEPROM_SIZE 512
// Zero based

#define RELAY_DATA_PIN 14
#define RELAY_LATCH_PIN 12
#define RELAY_CLOCK_PIN 13
#define RELAY_OE_PIN 5
const int CHANNEL_PINS[] = {15, 13, 12, 14, 16};


