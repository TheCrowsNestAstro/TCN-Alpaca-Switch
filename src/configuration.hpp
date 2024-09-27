#pragma once

//#define ESP32

#define SERVER_NAME "TCN"
#define MANUFACTURER "Christian Kardach"
#define MANUFACTURER_VERSION "1.0"
#define LOCATION "SE"

#define DEVICE_NAME "TCN Power Switch"
#define DEVICE_TYPE "Switch"
#define DEVICE_NR 0
#define UNIQUE_CLIENT_ID "9be62a4558494b638924267778cd0350" // https://www.guidgenerator.com/online-guid-generator.aspx

#define DESCRIPTION "Mount ASCOM Switch for controlling power supplies"
#define DRIVER_INFO "TCN ASCOM Alpaca Driver"
#define DRIVER_VERSION "1.0"

// Zero based
#define NR_OF_RELAYS 8

#define RELAY_DATA_PIN 15
#define RELAY_LATCH_PIN 13
#define RELAY_CLOCK_PIN 12

#define DHT_PIN 14

#define USE_BITSHIFT 0


#define RELAY_PIN_0 19
#define RELAY_PIN_1 18
#define RELAY_PIN_2 17
#define RELAY_PIN_3 16
#define RELAY_PIN_4 27
#define RELAY_PIN_5 26
#define RELAY_PIN_6 25
#define RELAY_PIN_7 33


#define RELAY_0_NAME "Power Case Fan"
#define RELAY_1_NAME "PSU 24V"
#define RELAY_2_NAME "AllSky Heaters"
#define RELAY_3_NAME "OBS Heater"
#define RELAY_4_NAME "OBS Lights"
#define RELAY_5_NAME "Dome Power"
#define RELAY_6_NAME "Mount MKS"
#define RELAY_7_NAME "Mount Fan"

#define RELAY_0_DESC "Ventilation Fan"
#define RELAY_1_DESC "Main 24V PSU unit"
#define RELAY_2_DESC "AllSky dome/rain heaters"
#define RELAY_3_DESC "Observatory heater/ventilation"
#define RELAY_4_DESC "Observatory lights"
#define RELAY_5_DESC "Dome 12V power supply"
#define RELAY_6_DESC "Mount MKS power"
#define RELAY_7_DESC "Primary mirror cooling fan"

