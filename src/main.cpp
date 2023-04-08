#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <arduino-timer.h>
#include <ArduinoLog.h>
#include <PubSubClient.h>

#include "arduino_secrets.h"
#include "configuration.hpp"
#include "device\switchHandler.h"

#include "html.h"

int status = WL_IDLE_STATUS;
///////enter your sensitive data in the Secret tab/arduino_secrets.h
char hostname[] = _HOSTNAME;
char ssid[] = _SSID;     // your network SSID (name)
char pass[] = _PASSWORD; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;        // your network key Index number (needed only for WEP)


// MQTT Broker
IPAddress mqtt_server = MQTT_HOST;
const char *topic = MQTT_TOPIC;
const int mqtt_port = MQTT_PORT; //1883;
const char *mqtt_user = MQTT_USER; //"chris";
const char *mqtt_password = MQTT_PASS; // "wandasee2me3";
// end of MQTT

unsigned int localPort = 32227;  // The Alpaca Discovery test port
unsigned int alpacaPort = 11111; // The (fake) port that the Alpaca API would be available on
char packetBuffer[255]; // buffer to hold incoming packet

ESP8266WebServer *server = new ESP8266WebServer(alpacaPort);
ESP8266HTTPUpdateServer updater;
WiFiUDP Udp;
ESP8266WebServer webServer(80);

// MQTT
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

SwitchHandler *device = new SwitchHandler(server);

auto timer = timer_create_default();

// Forward declarations
void handleRoot();
void handleUpdate();
void handleEdit();
void handleRename();
void printWifiStatus();
void callback(char* topic, byte* payload, unsigned int length);

// WIFI
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi sucessfully.");
  if(MDNS.begin(mDNS_NAME)) {
    Log.infoln("MDNS started");
  }
  printWifiStatus();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi, trying to connect...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
}

// MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.publish(MQTT_TOPIC, "Switch is running");
      // client.subscribe("inTopic");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

bool publishStatus(void *)
{
  if(client.connected())
  {
    String output = device->getSwitchState();
    Log.traceln(output.c_str());
    client.publish(MQTT_TOPIC, output.c_str());

  }
  return true;
}

// ALPACA
void CheckForDiscovery()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Log.traceln("Received packet of size: %d" CR, packetSize);
    IPAddress remoteIp = Udp.remoteIP();
    Log.traceln("From %s , on port %d" CR, remoteIp.toString().c_str(), Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      // Ensure that it is null terminated
      packetBuffer[len] = 0;
    }
    Log.traceln("Contents: %s" CR, packetBuffer);

    // No undersized packets allowed
    if (len < 16)
    {
      return;
    }

    if (strncmp("alpacadiscovery1", packetBuffer, 16) != 0)
    {
      return;
    }

    char response[36] = {0};
    sprintf(response, "{\"AlpacaPort\": %d}", alpacaPort);

    uint8_t buffer[36] = "{\"AlpacaPort\": 11111}";

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(buffer, 36);
    Udp.endPacket();
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Log.traceln(F("SSID: %s" CR), WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Log.traceln(F("IP Address: %s" CR), ip.toString().c_str());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Log.traceln("signal strength (RSSI): %l dBm" CR, rssi);
}

void handleMgmtVersions() { device->handlerMgmtVersions(); }
void handleMgmtDescription() { device->handlerMgmtDescription(); }
void handleMgmtConfiguredDevices() { device->handlerMgmtConfiguredDevices(); }

void handleConnected() { device->handlerConnected(); }
void handleDescriptionGet() { device->handlerDescriptionGet(); }
void handleDriverInfoGet() { device->handlerDriverInfoGet(); }
void handleDriverVersionGet() { device->handlerDriverVersionGet(); }
void handleInterfaceVersionGet() { device->handlerInterfaceVersionGet(); }
void handleNameGet() { device->handlerNameGet(); }
void handleSupportedActionsGet() { device->handlerSupportedActionsGet(); }

void handleAction() { device->handleAction(); }
void handleCommandBlind() { device->handleCommandBlind(); }
void handleCommandBool() { device->handleCommandBool(); }
void handleCommandString() { device->handleCommandString(); }

void handleDriver0Maxswitch() { device->handlerDriver0Maxswitch(); }
void handleDriver0CanWrite() { device->handlerDriver0CanWrite(); }
void handleDriver0SwitchDescription() { device->handlerDriver0SwitchDescription(); }
void handleDriver0SwitchState() { device->handlerDriver0SwitchState(); }
void handleDriver0SwitchName() { device->handlerDriver0SwitchName(); }
void handleDriver0SwitchValue() { device->handlerDriver0SwitchValue(); }
void handleDriver0MinSwitchValue() { device->handlerDriver0MinSwitchValue(); }
void handleDriver0MaxSwitchValue() { device->handlerDriver0MaxSwitchValue(); }
void handleDriver0SwitchStep() { device->handlerDriver0SwitchStep(); }

/******************************************
 * SETUP
 ******************************************/
void setup()
{
  Serial.begin(115200);
  
  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_TRACE, &Serial);

  Log.infoln("Connecting to WIFI...");

  // Some ESP8266 modules broadcast their own network, this turns that off
  //WiFi.mode(WIFI_STA);
  WiFi.hostname(mDNS_NAME);

  //Register event handlers
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  // attempt to connect to the Wifi network defined in arduino_secrets.h
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Log.traceln(".");
  }

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  timer.every(5000, publishStatus);

  //Log.infoln("Connected to wifi");
  // printWifiStatus();

  // Management API
  server->on("/management/apiversions", HTTP_GET, handleMgmtVersions);
  server->on("/management/v1/description", HTTP_GET, handleMgmtDescription);
  server->on("/management/v1/configureddevices", HTTP_GET, handleMgmtConfiguredDevices);

  server->on("/api/v1/switch/0/connected", HTTP_ANY, handleConnected);
  server->on("/api/v1/switch/0/description", HTTP_GET, handleDescriptionGet);
  server->on("/api/v1/switch/0/driverinfo", HTTP_GET, handleDriverInfoGet);
  server->on("/api/v1/switch/0/driverversion", HTTP_GET, handleDriverVersionGet);
  server->on("/api/v1/switch/0/interfaceversion", HTTP_GET, handleInterfaceVersionGet);
  server->on("/api/v1/switch/0/name", HTTP_GET, handleNameGet);
  server->on("/api/v1/switch/0/supportedactions", HTTP_GET, handleSupportedActionsGet);

  server->on("/api/v1/switch/0/action", HTTP_PUT, handleAction);
  server->on("/api/v1/switch/0/commandblind", HTTP_PUT, handleCommandBlind);
  server->on("/api/v1/switch/0/commandbool", HTTP_PUT, handleCommandBool);
  server->on("/api/v1/switch/0/commandstring", HTTP_PUT, handleCommandString);

  // Switch-specific functions
  server->on("/api/v1/switch/0/maxswitch", HTTP_GET, handleDriver0Maxswitch);
  server->on("/api/v1/switch/0/canwrite", HTTP_GET, handleDriver0CanWrite);
  server->on("/api/v1/switch/0/getswitchdescription", HTTP_GET, handleDriver0SwitchDescription);
  server->on("/api/v1/switch/0/getswitch", HTTP_GET, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/setswitch", HTTP_PUT, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/getswitchname", HTTP_GET, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/setswitchname", HTTP_PUT, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/getswitchvalue", HTTP_GET, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/setswitchvalue", HTTP_PUT, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/minswitchvalue", HTTP_GET, handleDriver0MinSwitchValue);
  server->on("/api/v1/switch/0/maxswitchvalue", HTTP_GET, handleDriver0MaxSwitchValue);
  server->on("/api/v1/switch/0/switchstep", HTTP_GET, handleDriver0SwitchStep);

  /*
  //Custom
  server.on("/status",                              HTTP_GET, handlerStatus);
  server.on("/restart",                             HTTP_ANY, handlerRestart);
  */

  updater.setup(server);
  server->begin();
  Log.infoln("Alpaca server handlers setup & started...");
  Log.infoln("Listening for Alpaca discovery requests...");

  Udp.begin(localPort);

  // connectToRedis();

  // Webserver
  webServer.on("/", handleRoot);
  webServer.on("/edit", handleEdit);
  webServer.on("/rename", HTTP_POST, handleRename);
  webServer.on("/update", HTTP_GET, handleUpdate);

  webServer.begin();

}

void handleRoot() {
  String result = index_html_header;
  result += "<table class=\"center\">";

  for(int i=1; i<=NR_OF_RELAYS; i+=2){
    String relayStateValue = "";
    if(device->getSwitchState(i-1) == true)
    {
      relayStateValue = "checked";
    }

    result += "<tr class=\"tr-main\">";
    result += "<td class=\"td-first\">";
    result += "<label>";
    result += "<input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +">";
    result += "<span class=\"slider\"></span>";
    result += "</label>";
    result += "</td>";
    result += "<td class=\"name-title\">";
    result += device->getSwitchName(i-1);
    result += "</td>";

    relayStateValue = "";
    if(device->getSwitchState(i) == true)
    {
      relayStateValue = "checked";
    }

    result += "<td class=\"td-second\">";
    result += "<label>";
    result += "<input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i+1) + "\" "+ relayStateValue +">";
    result += "<span class=\"slider\"></span>";
    result += "</label>";
    result += "</td>";
    result += "<td class=\"name-title\">";
    result += device->getSwitchName(i);
    result += "</td>";

    result += "</tr>";
  }
  result += "</table>";
  result += index_html_footer;
  webServer.send(200, "text/html", result);   // Send HTTP status 200 (Ok) and send some text to the browser/client

}

void handleUpdate() {         
  String message = "";

  int id = webServer.arg("relay").toInt();
  int state = webServer.arg("state").toInt();
  Log.traceln(F("Web submit switch nr: %d %T" CR), id, state);

  device->setSwitchState(id-1, bool(state));

  webServer.send(200, "text/plain", "ok");           
}

void handleEdit()
{
  String result = edit_html_header;
  result += "<form action=\"/rename\" method=\"POST\">";

  for(int i=1; i<=NR_OF_RELAYS; i++){
    result += "<label for=\"ch"+String(i)+"\">Channel "+String(i)+"</label>";
    result += "<input type=\"text\" id=\"ch"+String(i)+"\" name=\"ch" + String(i) + "\" placeholder=\"Channel 1..\" value=\""+device->getSwitchName(i-1)+"\">";
  }
  result += "<input type=\"submit\" value=\"Save\" style=\"margin-top: 10px;\"></form>";

  result += edit_html_footer;
  webServer.send(200, "text/html", result);
}

void handleRename()
{
  for(int i=1; i<=NR_OF_RELAYS; i++){
    String chName = webServer.arg("ch"+String(i));
    Log.traceln(F("Name: %c" CR), chName.c_str());
    device->setSwitchName(i-1, chName);
  }
  
  device->storeEEPROM();

  webServer.sendHeader("Location", String("/"), true);
  webServer.send ( 302, "text/plain", "");
}

void loop()
{
  server->handleClient();
  webServer.handleClient();
  CheckForDiscovery();

  // MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  MDNS.update();

  // CHECK
  timer.tick();

}