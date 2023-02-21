#include "device\switchHandler.h"


SwitchHandler::SwitchHandler(ESP8266WebServer *server)
{
    _server = server;
    switchDevice = new SwitchDevice();
    // switchDevice->writeEEPROM();
    switchDevice->readEEPROM();

    serverTransactionID = 0;
}

void SwitchHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.traceln("%d" CR, i);
        Log.traceln("%s" CR, _server->argName(i));
        Log.traceln("%s" CR, _server->arg(i));
        Log.traceln("--------------------------");
    }
}

void SwitchHandler::incrementServerTransID()
{
    serverTransactionID++;
}

void SwitchHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnIntValue(int val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}
/*
 * ALPACA DEVICE MANAGEMENT
 */

void SwitchHandler::handlerMgmtVersions()
{
    Log.traceln("handlerMgmtVersions called...");
    incrementServerTransID();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void SwitchHandler::handlerMgmtDescription()
{
    Log.traceln("handlerMgmtDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "text/json", output);
        
    }
}

void SwitchHandler::handlerMgmtConfiguredDevices()
{
    Log.traceln("handlerMgmtConfiguredDevices called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "text/json", output);
        
    }
}

void SwitchHandler::handlerConnected()
{
    Log.traceln("handlerConnected called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");

        String deviceType = _server->arg("device_type");
        //uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(switchDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        Log.traceln("handlerConnected POST called");

        // String _connected = _server->arg("Connected");
        switchDevice->connected = (bool)_server->arg("Connected");
        // Log.traceln("%t", CR, switchDevice->connected);

        returnEmpty("", 0);
    }
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void SwitchHandler::handlerDescriptionGet()
{
    Log.traceln("handlerDescriptionGet called");
    returnStringValue(DESCRIPTION, "", 0);
}

void SwitchHandler::handlerDriverInfoGet()
{
    Log.traceln("handlerDriverInfoGet called");
    returnStringValue(DRIVER_INFO, "", 0);
}

void SwitchHandler::handlerDriverVersionGet()
{
    Log.traceln("handlerDriverVersionGet called");
    returnStringValue(DRIVER_VERSION, "", 0);
}

void SwitchHandler::handlerInterfaceVersionGet()
{
    Log.traceln("handlerInterfaceVersionGet called");
    returnIntValue(1, "", 0);
}

void SwitchHandler::handlerNameGet()
{
    Log.traceln("handlerNameGet called");
    returnStringValue(DEVICE_NAME, "", 0);
}

void SwitchHandler::handlerSupportedActionsGet()
{
    Log.traceln("handlerSupportedActionsGet called");

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");
    array.add("maxswitch");
    array.add("canwrite");
    array.add("getswitchdescription");
    array.add("getswitch");
    array.add("getswitchname");
    array.add("getswitchvalue");
    array.add("minswitchvalue");
    array.add("maxswitchvalue");
    array.add("switchstep");

    returnJsonArrayValue(array, "", 0);
    
}

void SwitchHandler::handleAction()
{
    Log.traceln("handleAction called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void SwitchHandler::handleCommandBlind()
{
    Log.traceln("handleCommandBlind called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnEmpty("", 0);
}

void SwitchHandler::handleCommandBool()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void SwitchHandler::handleCommandString()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command.c_str());
    Log.traceln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

/***********************************
 * ASCOM SWITCH
 **********************************/
void SwitchHandler::handlerDriver0Maxswitch()
{
    Log.traceln("handlerDriver0Maxswitch called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(NR_OF_RELAYS, "", 0);
}

void SwitchHandler::handlerDriver0CanWrite()
{
    Log.traceln("handlerDriver0CanWrite called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true, "", 0);
}

void SwitchHandler::handlerDriver0SwitchDescription()
{
    Log.traceln("handlerDriver0SwitchDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnStringValue(switchDevice->channelDesc[id], "", 0);
}

void SwitchHandler::handlerDriver0SwitchState()
{
    Log.traceln("handlerDriver0SwitchState called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchState called");

        returnBoolValue(switchDevice->getRelayState(id), "", 0);
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchState called");
        bool val = (bool)_server->arg("State");

        switchDevice->setRelayState(id, val);
        returnEmpty("", 0);
    }
}

void SwitchHandler::handlerDriver0SwitchName()
{
    Log.traceln("handlerDriver0SwitchName called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    returnStringValue(switchDevice->channelNames[id], "", 0);
}

void SwitchHandler::handlerDriver0SwitchValue()
{
    Log.traceln("handlerDriver0SwitchValue called");
    //debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchValue called");
        returnDoubleValue(switchDevice->getRelayStateDouble(id), "", 0);
        
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchValue called");
        double val = (double)_server->arg("Value").toDouble();
        
        switchDevice->setRelayValue(id, val);
        returnEmpty("", 0);
    }


}

void SwitchHandler::handlerDriver0MinSwitchValue()
{
    Log.traceln("handlerDriver0MinSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(0.0, "", 0);
}

void SwitchHandler::handlerDriver0MaxSwitchValue()
{
    Log.traceln("handlerDriver0MaxSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}

void SwitchHandler::handlerDriver0SwitchStep()
{
    Log.traceln("handlerDriver0SwitchStep called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}

//***********************************************
//          CUSTOM HANDLERS
//***********************************************
bool SwitchHandler::getSwitchState(int id)
{
    return switchDevice->getRelayState(id);
}

void SwitchHandler::setSwitchState(int id, bool state)
{
    switchDevice->setRelayState(id, state);
}

String SwitchHandler::getSwitchName(int id)
{
    return switchDevice->channelNames[id];
}

void SwitchHandler::setSwitchName(int id, String name)
{
    switchDevice->channelNames[id] = name;
}

void SwitchHandler::storeEEPROM()
{
    switchDevice->writeEEPROM();
}